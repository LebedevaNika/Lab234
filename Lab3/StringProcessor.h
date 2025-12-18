#pragma once
#include "DoubleList.h"
#include <sstream>
#include <cctype>
#include <string>

class StringProcessor {
private:
    static bool startsWithA(const std::string& word) {
        if (word.empty()) return false;
        return std::tolower(word[0]) == 'a';
    }

    static std::string cleanWord(const std::string& word) {
        std::string result;
        for (char c : word) {
            if (std::isalpha(c)) {
                result += c;
            }
        }
        return result;
    }

public:
    static std::string process(const std::string& input) {
        if (input.empty()) return "";  // Если строка пустая

        std::string result;  // Сюда будем собирать результат
        std::istringstream iss(input);  // "Разбиватель" строк на слова
        std::string word;
        bool first = true;  // Флаг для первого слова

        while (iss >> word) {  // Читаем слово за словом
            if (!first) {
                result += " ";  // Добавляем пробел между словами
            }
            first = false;

            std::string clean = cleanWord(word);  // Чистим от знаков препинания

            if (clean.empty()) {
                result += word;  // Если слово было только из знаков препинания
            }
            else if (startsWithA(clean) && clean.length() > 3) {
                // НАША ОСНОВНАЯ ЛОГИКА:
                // Если слово начинается на 'a' и длиннее 3 букв
                result += std::to_string(clean.length());  // Заменяем на длину
            }
            else {
                result += clean;  // Иначе оставляем как есть
            }
        }

        return result;
    }
};
