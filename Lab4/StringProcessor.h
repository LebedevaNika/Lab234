#pragma once
#include "DoubleList.h"
#include <sstream>
#include <cctype>
#include <string>

class StringProcessor {
private:
    static bool startsWithA(const std::string& word) {
        if (word.empty()) return false;
        char firstChar = static_cast<char>(std::tolower(static_cast<unsigned char>(word[0])));
        return firstChar == 'a';
    }

    static std::string cleanWord(const std::string& word) {
        std::string result;
        for (char c : word) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                result += c;
            }
        }
        return result;
    }

public:
    static std::string process(const std::string& input) {
        if (input.empty()) return "";

        std::string result;
        std::istringstream iss(input);
        std::string word;
        bool first = true;

        while (iss >> word) {
            if (!first) {
                result += " ";
            }
            first = false;

            std::string clean = cleanWord(word);

            if (clean.empty()) {
                result += word;
            }
            else if (startsWithA(clean) && clean.length() > 3) {
                result += std::to_string(clean.length());
            }
            else {
                result += clean;
            }
        }

        return result;
    }
};
