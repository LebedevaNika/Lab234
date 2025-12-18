#include "pch.h"
#include <cstring>
#include <cstdlib>
#include <cctype>

char* processString(char* str) //обработка строки
{
    int len = strlen(str);
    char* result = (char*)malloc(len * 2 + 1); // Выделяем память для результата
    int pos = 0; //Позиция для записи в result

    for (int i = 0; i < len;)
    {
        if (isalpha(str[i]))
        {
            int start = i;
            while (i < len && isalpha(str[i])) i++; // Пропускаем все буквы слова
            int wordLen = i - start; // Вычисляем длину слова

            if (str[start] == 'a' && wordLen > 3)
            {
                pos += sprintf(result + pos, "%d", wordLen); // Заменяем слово на его длину, указатель на место записи, число в строку
            }
            else
            {
                strncpy(result + pos, str + start, wordLen);// Копируем слово как есть куда откуда сколько
                pos += wordLen;
            }
        }
        else
        {
            result[pos++] = str[i++];
        }
    }

    result[pos] = '\0';
    return result;
}

char* inputWithMalloc(const char* input) //ввод строки
{
    char* str = nullptr;  // Изначально пустой указатель
    int size = 0;  // Текущая длина строки

    for (int i = 0; input[i] != '\0'; i++)  // Проходим по всем символам входной строки
    {
        // Выделяем память на 1 символ больше
        char* temp = (char*)malloc(size + 2);  // +2: для нового символа + '\0'

        // Копируем старые символы
        for (int j = 0; j < size; j++)
            temp[j] = str[j];

        // Добавляем новый символ
        temp[size++] = input[i];  // size++ увеличивает size после присваивания
        temp[size] = '\0';  // Завершающий нуль

        // Освобождаем старую память
        free(str);
        str = temp;  // Используем новую память
    }
    return str;
}
