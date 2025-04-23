#include "SfxExtractor.h"
#include "soh/Enhancements/speechsynthesizer/SpeechSynthesizer.h"
#include "soh/Enhancements/tts/tts.h"
#include "dr_libs/dr_wav.h"
#define MA_NO_FLAC
#define MA_NO_MP3
#define MA_NO_THREADING
#define MA_NO_DEVICE_IO
#define MA_NO_GENERATION
#define MA_ENABLE_ONLY_SPECIFIC_BACKENDS
#include "miniaudio/miniaudio.h"
#include "soh/OTRGlobals.h"
#include "SfxTable.h"
#include <sstream>
extern "C" {
#include "z64.h"
#include "functions.h"
#include "variables.h"
void AudioMgr_CreateNextAudioBuffer(s16* samples, u32 num_samples);
extern bool freezeGame;
}
enum {
    STEP_SETUP = 0,
    STEP_MAIN,
    STEP_FINISHED,
    STEP_ERROR,
    STEP_ERROR_OTR, // File exists.

} SFX_EXTRACTION_STEPS;
enum {
    CT_WAITING, // for a sound to start ripping.
    CT_PRIMING,
    CT_READY,    // to start ripping a sound.
    CT_FINISHED, // ripping the current sound.
    CT_SHUTDOWN,
} CAPTURE_THREAD_STATES;
#define SFX_EXTRACTION_BUFFER_SIZE 44100 * 15
#define SFX_EXTRACTION_ONE_FRAME 736
bool SfxExtractor::isAllZero(int16_t* buffer, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (buffer[i] != 0)
            return false;
    }
    return true;
}

// Find the beginning of a captured signal.
size_t SfxExtractor::adjustedStartOfInput() {
    size_t startOfInput = 0;
    while (startOfInput + 2 < SFX_EXTRACTION_BUFFER_SIZE * 2 &&
           (tempBuffer[startOfInput] == 0 || tempBuffer[startOfInput + 1] == 0)) {
        startOfInput += 2;
    }
    return startOfInput;
}

size_t SfxExtractor::adjustedEndOfInput(size_t endOfInput) {
    while (endOfInput > 0 && (tempBuffer[endOfInput] == 0 || tempBuffer[endOfInput - 1] == 0)) {
        endOfInput -= 2;
    }
    return endOfInput;
}

bool SfxExtractor::renderOutput(size_t endOfInput) {
    size_t startOfInput = adjustedStartOfInput();
    endOfInput = adjustedEndOfInput(endOfInput);
    if (endOfInput <= startOfInput) {
        return true;
    }

    ma_channel_converter_config config =
        ma_channel_converter_config_init(ma_format_s16, 2, NULL, 1, NULL, ma_channel_mix_mode_default);
    ma_channel_converter converter;
    if (ma_channel_converter_init(&config, NULL, &converter) != MA_SUCCESS)
        throw std::runtime_error("SfxExtractor: Unable to initialize channel converter.");
    drwav_data_format format;
    format.bitsPerSample = 16;
    format.channels = 1;
    format.container = drwav_container_riff;
    format.format = DR_WAVE_FORMAT_PCM;
    format.sampleRate = 44100;
    drwav wav;
    std::string fileName = getExternalFileName(currentSfx);
    void* mem = NULL;
    size_t size = 0;

    if (!drwav_init_memory_write(&wav, &mem, &size, &format, NULL))
        throw std::runtime_error("SfxExtractor: Unable to initialize wave writer.");
    int16_t chunk[64];
    int16_t* mark = tempBuffer + startOfInput;
    size_t samplesLeft = endOfInput - startOfInput;
    while (samplesLeft > 0) {
        size_t thisChunk = std::min<size_t>(64, samplesLeft);
        ma_channel_converter_process_pcm_frames(&converter, chunk, mark, thisChunk / 2);
        drwav_write_pcm_frames(&wav, thisChunk / 2, chunk);
        samplesLeft -= thisChunk;
        mark += thisChunk;
    }
    drwav_uninit(&wav);
    std::vector<uint8_t> fileData((uint8_t*)mem, (uint8_t*)mem + size);
    drwav_free(mem, nullptr);
    return archive->WriteFile(fileName.c_str(), fileData);
}

void SfxExtractor::setup() {
    try {
        SpeechSynthesizer::Instance->Speak(
            "Sfx extraction speedrun initiated. Please wait. This will take a few minutes.", "en-US");
        // Kill the audio thread so we can take control.
        captureThreadState = CT_WAITING;
        OTRAudio_InstallSfxCaptureThread();
        // Make sure we're starting from a clean slate.
        std::string sohAccessibilityPath = Ship::Context::GetPathRelativeToAppDirectory("accessibility.o2r");
        if (std::filesystem::exists(sohAccessibilityPath)) {
            currentStep = STEP_ERROR_OTR;
            return;
        }
        // Over-allocated just a tad because otherwise we'll overrun if the last frame is short.
        tempStorage.resize((SFX_EXTRACTION_BUFFER_SIZE + (SFX_EXTRACTION_ONE_FRAME * 3)) * 2, 0);
        tempBuffer = tempStorage.data();

        sfxToRip = 0;
        currentStep = STEP_MAIN;
        archive = std::make_shared<Ship::O2rArchive>("accessibility.o2r");
        archive->Open();
    } catch (...) { currentStep = STEP_ERROR; }
}

void SfxExtractor::ripNextSfx() {
    {
        auto lock = OTRAudio_Lock();
        if (captureThreadState == CT_READY || captureThreadState == CT_PRIMING)
            return; // Keep going.
    }
    // Was the last sfx a loop? If so then we need to stop it, and then we need to run audio out to nowhere for as long
    // as it takes to get back to a blank slate.
    if (currentSfx != -1) {
        Audio_StopSfxByPos(&gSfxDefaultPos);
        captureThreadState = CT_PRIMING;
        currentSfx = -1;

        return;
    }
    if (sfxToRip == sfxCount) {
        currentStep = STEP_FINISHED; // Caught 'em all!
        return;
    }

    currentSfx = sfxTable[sfxToRip++];
    Audio_PlaySoundGeneral(currentSfx, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                           &gSfxDefaultReverb);

    {
        auto lock = OTRAudio_Lock();
        captureThreadState = CT_READY;
    }
    maybeGiveProgressReport();
}
void SfxExtractor::finished() {
    OTRAudio_UninstallSfxCaptureThread(); // Returns to normal audio opperation.
    CVarClear("gExtractSfx");
    CVarSave();
    archive->Close();
    archive = nullptr;
    freezeGame = false;

    Audio_QueueSeqCmd(NA_BGM_TITLE);

    if (currentStep == STEP_ERROR || currentStep == STEP_ERROR_OTR) {
        Audio_PlaySoundGeneral(NA_SE_SY_ERROR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                               &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        Audio_PlaySoundGeneral(NA_SE_EN_GANON_LAUGH, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                               &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
        std::stringstream ss;
        ss << "Sorry, we tried to extract the sound effects, but Ganondorf overruled us with an iron fist."
           << std::endl;
        if (currentStep == STEP_ERROR_OTR)
            ss << "In all seriousness, please delete accessibility.o2r and try again.";
        SpeechSynthesizer::Instance->Speak(ss.str().c_str(), "en-US");
    } else
        Audio_PlayFanfare(NA_BGM_ITEM_GET);
}
void SfxExtractor::maybeGiveProgressReport() {
    for (int i = 0; i < 9; i++) {
        if (sfxToRip == sfxCount * (i + 1) / 10) {
            std::stringstream ss;
            ss << (i + 1) * 10 << " percent complete.";
            SpeechSynthesizer::Instance->Speak(ss.str().c_str(), "en-US");
        }
    }
}

SfxExtractor::SfxExtractor() {
    currentStep = STEP_SETUP;
}

void SfxExtractor::frameCallback() {
    switch (currentStep) {
        case STEP_SETUP:
            setup();
            break;
        case STEP_MAIN:
            ripNextSfx();
            break;
        default: // Handles finished as well as a number of error conditions.
            finished();
    }
}

void SfxExtractor::prime() {
    while (true) {
        AudioMgr_CreateNextAudioBuffer(tempBuffer, SFX_EXTRACTION_ONE_FRAME);
        if (isAllZero(tempBuffer, SFX_EXTRACTION_ONE_FRAME * 2))
            break;
    }
    captureThreadState = CT_FINISHED;
}

void SfxExtractor::captureCallback() {
    if (captureThreadState == CT_PRIMING)
        prime();
    if (captureThreadState != CT_READY)
        return; // No work to do at the moment.
    memset(tempBuffer, 0, SFX_EXTRACTION_BUFFER_SIZE * 4);
    int16_t* mark = tempBuffer;
    size_t samplesLeft = SFX_EXTRACTION_BUFFER_SIZE;
    bool outputStarted = false;
    size_t endOfInput = 0;
    int waitTime = 0;
    while (samplesLeft > 0) {
        AudioMgr_CreateNextAudioBuffer(mark, SFX_EXTRACTION_ONE_FRAME);

        if (isAllZero(mark, SFX_EXTRACTION_ONE_FRAME * 2)) {
            if (outputStarted) {
                break;
            } else if (waitTime++ < 300) {
                continue; // Output is silent, allow more time for audio to begin.
            }
            captureThreadState = CT_FINISHED; // Sound is unavailable, so skip over it and move on.
            return;
        }

        outputStarted = true;
        mark += (SFX_EXTRACTION_ONE_FRAME * 2);
        endOfInput += (SFX_EXTRACTION_ONE_FRAME * 2);
        samplesLeft -= std::min<size_t>(SFX_EXTRACTION_ONE_FRAME, samplesLeft);
    }
    if (renderOutput(endOfInput)) {
        captureThreadState = CT_FINISHED;
    } else {
        SPDLOG_ERROR("failed to write file to archive, trying again");
    }
}
std::string SfxExtractor::getExternalFileName(int16_t sfxId) {
    std::stringstream ss;
    ss << "accessibility/audio/";
    ss << std::hex << std::setw(4) << std::setfill('0') << sfxId << ".wav";
    return ss.str();
}
