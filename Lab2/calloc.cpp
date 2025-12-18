#include "pch.h"
#include <cstring>
#include <cstdlib>

char* inputWithCalloc(const char* input)
{
    int capacity = 5;      // Начальная вместимость - 5 символов
    int size = 0;          
    char* str = (char*)calloc(capacity, sizeof(char));  // Выделяем память

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (size + 1 >= capacity)
        {
            capacity += 5;                    // Увеличиваем вместимость на 5
            str = (char*)realloc(str, capacity);  // Перевыделяем память
        }
        str[size++] = input[i]; // Добавляем символ в строку
    }
    str[size] = '\0';
    return str;
}
