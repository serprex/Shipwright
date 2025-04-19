#include "ESpeakSpeechSynthesizer.h"
extern "C" {
#include <espeak-ng/speak_lib.h>
}

ESpeakSpeechSynthesizer::ESpeakSpeechSynthesizer() {
}

bool ESpeakSpeechSynthesizer::DoInit() {
    return espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 100, NULL, 0) != -1;
}

void ESpeakSpeechSynthesizer::DoUninitialize() {
    espeak_Terminate();
}

void ESpeakSpeechSynthesizer::Speak(const char* text, const char* language) {
    if (language != this->mLanguage) {
        espeak_VOICE voice = { .languages = language };
        if (espeak_SetVoiceByProperties(&voice)) {
            return;
        }
        this->mLanguage = language;
    }
    espeak_Synth(text, 100, 0, POS_CHARACTER, 0, espeakCHARS_UTF8, NULL, NULL);
}
