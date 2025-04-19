#pragma once

#include "SpeechSynthesizer.h"

class ESpeakSpeechSynthesizer : public SpeechSynthesizer {
  public:
    ESpeakSpeechSynthesizer();

    void Speak(const char* text, const char* language);

  protected:
    bool DoInit(void);
    void DoUninitialize(void);

  private:
    const char* mLanguage;
};
