#include "pch.h"
#include <fstream>
#include <cstdlib>
#include <cstring>

char* processString(char* str);

void fileProcess(const char* input, const char* filename)
{
    std::ofstream out(filename);  // Создаем поток для ЗАПИСИ в файл
    out << input;                 // Записываем строку в файл
    out.close();                  // Закрываем файл

    std::ifstream in(filename);   // Создаем поток для ЧТЕНИЯ из файла
    std::string temp, line;       // Временные переменные
    while (getline(in, temp))     // Читаем файл ПОСТРОЧНО
        line += temp;             // Складываем все строки в одну
    in.close();                   // Закрываем файл

    char* data = (char*)malloc(line.size() + 1);  // Выделяем память
    strcpy(data, line.c_str());                   // Копируем string в char*

    char* result = processString(data);

    std::ofstream out2(filename);  // Открываем файл ЗАНОВО для записи
    out2 << result;                // Записываем результат
    out2.close();                  // Закрываем

    free(data);    // Освобождаем data ("apple banana")
    free(result);  // Освобождаем result ("5 banana")
}
