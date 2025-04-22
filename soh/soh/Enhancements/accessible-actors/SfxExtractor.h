#pragma once
#include "libultraship/libultraship.h"
class SfxExtractor {
    std::shared_ptr<Ship::Archive> archive;
    int currentStep;
    int captureThreadState;
    int sfxToRip;
    s16 currentSfx;
    std::vector<int16_t> tempStorage; // Stores raw audio data for the sfx currently being ripped.
    int16_t* tempBuffer;              // Raw pointer to the above vector.
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
