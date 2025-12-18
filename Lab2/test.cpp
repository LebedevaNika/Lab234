#include "pch.h"
#include "gtest/gtest.h"

// объявления функций
char* inputWithMalloc(const char* input);
char* inputWithCalloc(const char* input);
char* processString(char* str);
void fileProcess(const char* input, const char* filename);

//malloc
TEST(MallocTest, Simple)
{
    char* s = inputWithMalloc("apple dog");
    char* r = processString(s);
    EXPECT_STREQ(r, "5 dog");
    free(s);
    free(r);
}

TEST(MallocTest, NoReplace)
{
    char* s = inputWithMalloc("ant cat");
    char* r = processString(s);
    EXPECT_STREQ(r, "ant cat");
    free(s);
    free(r);
}

TEST(MallocTest, Mixed)
{
    char* s = inputWithMalloc("about a apple");
    char* r = processString(s);
    EXPECT_STREQ(r, "5 a 5");
    free(s);
    free(r);
}

// calloc
TEST(CallocTest, Simple)
{
    char* s = inputWithCalloc("apple dog");
    char* r = processString(s);
    EXPECT_STREQ(r, "5 dog");
    free(s);
    free(r);
}

TEST(CallocTest, ShortWords)
{
    char* s = inputWithCalloc("a an ant");
    char* r = processString(s);
    EXPECT_STREQ(r, "a an ant");
    free(s);
    free(r);
}

TEST(CallocTest, Multiple)
{
    char* s = inputWithCalloc("about apple car");
    char* r = processString(s);
    EXPECT_STREQ(r, "5 5 car");
    free(s);
    free(r);
}

// file
TEST(FileTest, FileReplace)
{
    fileProcess("apple dog", "test.txt");
    std::ifstream in("test.txt");
    std::string res;
    std::getline(in, res);
    EXPECT_EQ(res, "5 dog");
}

TEST(FileTest, FileNoReplace)
{
    fileProcess("ant cat", "test.txt");
    std::ifstream in("test.txt");
    std::string res;
    std::getline(in, res);
    EXPECT_EQ(res, "ant cat");
}

TEST(FileTest, FileMixed)
{
    fileProcess("about a apple", "test.txt");
    std::ifstream in("test.txt");
    std::string res;
    std::getline(in, res);
    EXPECT_EQ(res, "5 a 5");
}
