#include "pch.h"`   
#include "gtest/gtest.h"
#include "DoubleList.h"
#include "StringProcessor.h"

//базовые операции
TEST(DoubleListTest, BasicOperations) {
    DoubleList<int> list;

    // Пустой список
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isValid());

    // Добавление
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 20);
    EXPECT_TRUE(list.isValid());

    // Удаление
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_TRUE(list.isValid());

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 10);
    EXPECT_TRUE(list.isValid());

    // Вставка
    list.insert(1, 15);
    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.isValid());

    // Удаление по значению
    list.remove(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 15);
    EXPECT_TRUE(list.isValid());
}

// строка
TEST(StringProcessorTest, ProcessString) {
    EXPECT_EQ(StringProcessor::process("apple and an ant abracadabra but cat"),
        "5 and an ant 11 but cat");

    EXPECT_EQ(StringProcessor::process("an ant and"),
        "an ant and");

    EXPECT_EQ(StringProcessor::process("banana ball big small"),
        "banana ball big small");

    EXPECT_EQ(StringProcessor::process(""),
        "");
}

// сортировка
TEST(DoubleListSortTest, SortNumbers) {
    // Тест шейкерной сортировки
    {
        DoubleList<int> list;
        list.push_back(5);
        list.push_back(2);
        list.push_back(8);
        list.push_back(1);
        list.push_back(3);

        EXPECT_TRUE(list.isValid());
        list.cocktailSort();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 2);
        EXPECT_EQ(list[2], 3);
        EXPECT_EQ(list[3], 5);
        EXPECT_EQ(list[4], 8);
    }

    // Тест сортировки вставками с бинарным поиском
    {
        DoubleList<int> list;
        list.push_back(9);
        list.push_back(3);
        list.push_back(7);
        list.push_back(1);
        list.push_back(5);

        EXPECT_TRUE(list.isValid());
        list.insertionSortWithBinarySearch();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 3);
        EXPECT_EQ(list[2], 5);
        EXPECT_EQ(list[3], 7);
        EXPECT_EQ(list[4], 9);
    }
}

// ==================== ТЕСТ 4: СОРТИРОВКА СТРОК ====================
TEST(DoubleListSortTest, SortStrings) {
    DoubleList<std::string> list;
    list.push_back("zebra");
    list.push_back("apple");
    list.push_back("cherry");
    list.push_back("banana");
    list.push_back("date");

    EXPECT_TRUE(list.isValid());
    list.cocktailSort();
    EXPECT_TRUE(list.isValid());
    EXPECT_TRUE(list.isSorted());

    EXPECT_EQ(list[0], "apple");
    EXPECT_EQ(list[1], "banana");
    EXPECT_EQ(list[2], "cherry");
    EXPECT_EQ(list[3], "date");
    EXPECT_EQ(list[4], "zebra");
}

// ==================== ТЕСТ 5: ИНТЕГРАЦИОННЫЙ ТЕСТ ====================
TEST(IntegrationTest, ProcessAndSortSimple) {
    // Простой интеграционный тест без сложной логики
    DoubleList<std::string> words;

    // Заполняем список
    words.push_back("banana");
    words.push_back("apple");
    words.push_back("date");

    // Проверяем исходное состояние
    EXPECT_EQ(words.size(), 3);
    EXPECT_TRUE(words.isValid());

    // Сортируем
    words.cocktailSort();
    EXPECT_TRUE(words.isSorted());
    EXPECT_TRUE(words.isValid());

    // Проверяем сортировку
    EXPECT_EQ(words[0], "apple");
    EXPECT_EQ(words[1], "banana");
    EXPECT_EQ(words[2], "date");

    // Применяем обработку (вручную, без StringProcessor)
    for (int i = 0; i < words.size(); i++) {
        std::string& word = words[i];
        if (!word.empty() && std::tolower(word[0]) == 'a' && word.length() > 3) {
            word = std::to_string(word.length());
        }
    }

    // Проверяем результат
    EXPECT_EQ(words[0], "5");       // apple -> 5
    EXPECT_EQ(words[1], "banana");  // остается
    EXPECT_EQ(words[2], "date");    // остается

    // Снова сортируем
    words.insertionSortWithBinarySearch();
    EXPECT_TRUE(words.isSorted());
    EXPECT_TRUE(words.isValid());
}

// ==================== ТЕСТ 6: ГРАНИЧНЫЕ СЛУЧАИ ====================
TEST(DoubleListSortTest, EdgeCases) {
    // Пустой список
    {
        DoubleList<int> list;
        list.cocktailSort();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());
    }

    // Один элемент
    {
        DoubleList<int> list;
        list.push_back(42);
        list.cocktailSort();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());
        EXPECT_EQ(list[0], 42);
    }

    // Уже отсортированный список
    {
        DoubleList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);

        list.cocktailSort();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());
    }

    // Обратно отсортированный список
    {
        DoubleList<int> list;
        list.push_back(5);
        list.push_back(4);
        list.push_back(3);
        list.push_back(2);
        list.push_back(1);

        list.cocktailSort();
        EXPECT_TRUE(list.isValid());
        EXPECT_TRUE(list.isSorted());
        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[4], 5);
    }
}
