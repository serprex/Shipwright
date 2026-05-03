#include "text.h"
#include "soh/ShipUtils.h"

Text::Text() = default;

Text::Text(std::string english_, std::string french_, std::string german_)
    : english(std::move(english_)), french(std::move(french_)), german(std::move(german_)), spanish("") {
    spanish = english;
}

Text::Text(std::string english_, std::string french_, std::string german_, std::string spanish_)
    : english(std::move(english_)), french(std::move(french_)), german(std::move(german_)),
      spanish(std::move(spanish_)) {
}

Text::Text(std::string english_) : english(std::move(english_)), french(""), german(""), spanish("") {
    french = spanish = german = english;
}

const std::string& Text::GetEnglish() const {
    return english;
}

const std::string& Text::GetFrench() const {
    return french.length() > 0 ? french : english;
}

const std::string& Text::GetGerman() const {
    return german.length() > 0 ? german : english;
}

const std::string& Text::GetSpanish() const {
    return spanish.length() > 0 ? spanish : english;
}

const std::string& Text::GetForLanguage(uint8_t language) const {
    switch (language) {
        case 0:
            return GetEnglish();
        case 2:
            return GetFrench();
        case 1:
            return GetGerman();
        default:
            return GetEnglish();
    }
}

Text Text::operator+(const Text& right) const {
    return Text{
        english + right.GetEnglish(),
        french + right.GetFrench(),
        german + right.GetGerman(),
        spanish + right.GetSpanish(),
    };
}

Text Text::operator+(const std::string& right) const {
    return Text{
        english + right,
        french + right,
        german + right,
        spanish + right,
    };
}

bool Text::operator==(const Text& right) const {
    return english == right.english;
}

bool Text::operator==(const std::string& right) const {
    return english == right || french == right || german == right || spanish == right;
}

bool Text::operator!=(const Text& right) const {
    return !operator==(right);
}

static void replaceAll(std::string& target, const std::string& oldStr, const std::string& replacement) {
    size_t position = target.find(oldStr);
    while (position != std::string::npos) {
        target.replace(position, oldStr.length(), replacement);
        position = target.find(oldStr);
    }
}

void Text::Replace(const std::string& oldStr, const std::string& newStr) {
    for (std::string& str : { std::ref(english), std::ref(french), std::ref(german), std::ref(spanish) }) {
        replaceAll(str, oldStr, newStr);
    }
}

void Text::Replace(const std::string& oldStr, const Text& newText) {
    replaceAll(english, oldStr, newText.GetEnglish());
    replaceAll(french, oldStr, newText.GetFrench());
    replaceAll(german, oldStr, newText.GetGerman());
    replaceAll(spanish, oldStr, newText.GetSpanish());
}

static void replaceRandomVowel(std::string& target, uint64_t* randState) {
    std::vector<size_t> vowelPositions;

    for (size_t i = 0; i < target.size(); ++i) {
        char c = std::tolower(target[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            vowelPositions.push_back(i);
        }
    }

    if (vowelPositions.empty()) {
        return;
    }

    size_t pos = ShipUtils::RandomElement(vowelPositions, randState);

    const std::vector<char> vowels = { 'a', 'e', 'i', 'o', 'u' };
    char newVowel = ShipUtils::RandomElement(vowels, randState);

    if (std::isupper(target[pos])) {
        newVowel = std::toupper(newVowel);
    }

    target[pos] = newVowel;
}

void Text::ReplaceRandomVowel(uint64_t* randState) {
    for (std::string& str : { std::ref(english), std::ref(french), std::ref(german), std::ref(spanish) }) {
        replaceRandomVowel(str, randState);
    }
}

static void duplicateRandomLetter(std::string& target, uint64_t* randState) {
    std::vector<size_t> letterPositions;

    for (size_t i = 0; i < target.size(); ++i) {
        if (std::isalpha(target[i])) {
            letterPositions.push_back(i);
        }
    }

    if (letterPositions.empty()) {
        return;
    }

    size_t pos = ShipUtils::RandomElement(letterPositions, randState);

    char c = target[pos];

    target.insert(target.begin() + pos + 1, c);
}

void Text::DuplicateRandomLetter(uint64_t* randState) {
    for (std::string& str : { std::ref(english), std::ref(french), std::ref(german), std::ref(spanish) }) {
        duplicateRandomLetter(str, randState);
    }
}