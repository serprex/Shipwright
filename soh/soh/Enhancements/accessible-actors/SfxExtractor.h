#pragma once
#include "libultraship/libultraship.h"

#define SFX_EXTRACTION_BUFFER_SIZE 44100 * 15
#define SFX_EXTRACTION_ONE_FRAME 736

enum CaptureThreadStates {
    CT_WAITING, // for a sound to start ripping.
    CT_PRIMING,
    CT_READY,    // to start ripping a sound.
    CT_FINISHED, // ripping the current sound.
    CT_SHUTDOWN,
};

enum SfxExtractionSteps {
    STEP_SETUP = 0,
    STEP_MAIN,
    STEP_FINISHED,
    STEP_ERROR,
    STEP_ERROR_FILE_EXISTS,
};

class SfxExtractor {
    std::shared_ptr<Ship::Archive> archive;
    SfxExtractionSteps currentStep;
    CaptureThreadStates captureThreadState;
    int sfxToRip;
    s16 currentSfx;
    // Stores raw audio data for the sfx currently being ripped.
    int16_t tempBuffer[(SFX_EXTRACTION_BUFFER_SIZE + SFX_EXTRACTION_ONE_FRAME * 3) * 2];
    // Check if a buffer contains meaningful audio output.
    bool isAllZero(int16_t* buffer, size_t count);
    size_t adjustedStartOfInput();
    size_t adjustedEndOfInput(size_t endOfInput);
    bool renderOutput(size_t endOfInput);
    void setup();
    void ripNextSfx();
    void finished(); // Also handles failure.
    void maybeGiveProgressReport();

  public:
    SfxExtractor();

    void frameCallback();
    void prime();
    // The below is called by the (hijacked) audio thread.
    void captureCallback();
    static std::string getExternalFileName(int16_t sfxId);
};
