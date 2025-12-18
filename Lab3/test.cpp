#include "pch.h"
#include "gtest/gtest.h"
#include "DoubleList.h"
#include "StringProcessor.h"

// //базовые операции
TEST(DoubleListTest, BasicOperations) {
    DoubleList<int> list;

    // Проверяем пустой список
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);

    // Добавляем элементы
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 5);
    EXPECT_EQ(list.back(), 20);

    // Удаляем элементы
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 10);

    // Вставка
    list.insert(1, 15);
    EXPECT_EQ(list.size(), 2);

    // Удаление по значению
    list.remove(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 15);
}

// строки
TEST(StringProcessorTest, ProcessString) {
    // Тест 1: Стандартный случай
    std::string input1 = "apple and an ant abracadabra but cat";
    std::string result1 = StringProcessor::process(input1);

    // "apple" (5) -> "5"
    // "abracadabra" (11) -> "11"
    // Остальные остаются
    EXPECT_EQ(result1, "5 and an ant 11 but cat");

    // Тест 2: Слова длиной ≤ 3 не меняются
    std::string input2 = "an ant and";
    std::string result2 = StringProcessor::process(input2);
    EXPECT_EQ(result2, "an ant and");

    // Тест 3: Слова не на 'a' не меняются
    std::string input3 = "banana ball big small";
    std::string result3 = StringProcessor::process(input3);
    EXPECT_EQ(result3, "banana ball big small");
}

//  Комплексный тест со списком строк
TEST(IntegrationTest, ListStringProcessing) {
    // Создаем и заполняем список
    DoubleList<std::string> words;
    words.push_back("apple");
    words.push_back("and");
    words.push_back("an");
    words.push_back("ant");
    words.push_back("abracadabra");
    words.push_back("but");
    words.push_back("cat");

    // Обрабатываем каждое слово
    Node<std::string>* current = words.begin();
    while (current) {
        std::string& word = current->data;

        // Проверяем начинается ли с 'a' и длина > 3
        if (!word.empty() && std::tolower(word[0]) == 'a' && word.length() > 3) {
            word = std::to_string(word.length());
        }
        current = current->next;
    }

    // Проверяем результат
    current = words.begin();
    EXPECT_EQ(current->data, "5");      // apple -> 5
    current = current->next;
    EXPECT_EQ(current->data, "and");    // остается
    current = current->next;
    EXPECT_EQ(current->data, "an");     // остается
    current = current->next;
    EXPECT_EQ(current->data, "ant");    // остается
    current = current->next;
    EXPECT_EQ(current->data, "11");     // abracadabra -> 11
    current = current->next;
    EXPECT_EQ(current->data, "but");    // остается
    current = current->next;
    EXPECT_EQ(current->data, "cat");    // остается
}
