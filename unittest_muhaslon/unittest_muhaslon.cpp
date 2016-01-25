#include <gtest/gtest.h>
#include <tools.h>
#include <muhaslon.h>

TEST(TestWordDistance, Test1)
{
    EXPECT_EQ(WordDistance(L"����", L"����"), 1);
}

TEST(TestWordDistance, Test0)
{
    EXPECT_EQ(WordDistance(L"����", L"����"), 0);
}

TEST(TestWordDistance, TestInf)
{
    EXPECT_EQ(WordDistance(L"����", L"������"), std::numeric_limits<size_t>::max());
}

TEST(TestWordDistance, TestEmpty)
{
    EXPECT_EQ(WordDistance(L"", L""), 0);
}

TEST(TestMuhaSlon, Test1)
{
    std::vector<std::wstring> Dictionary{};
    MuhaSlon Test1{ Dictionary };
    std::vector<std::wstring> ExpectedRes{ L"����" };

    EXPECT_EQ(Test1.GetPath(L"����", L"����"), ExpectedRes);
}

TEST(TestMuhaSlon, Test0)
{
    std::vector<std::wstring> Dictionary{};
    MuhaSlon Test0{ Dictionary };
    std::vector<std::wstring> ExpectedRes{};

    EXPECT_EQ(Test0.GetPath(L"����", L"����"), ExpectedRes);
}

TEST(TestMuhaSlon, TestEthalon)
{
    std::vector<std::wstring> Dictionary{
        L"���",
        L"���",
        L"����",
        L"����",
        L"���",
        L"����",
        L"���"
    };

    MuhaSlon TestEthalon{ Dictionary };
    std::vector<std::wstring> ExpectedRes{ L"���", L"���", L"���" };

    EXPECT_EQ(TestEthalon.GetPath(L"���", L"���"), ExpectedRes);
}
