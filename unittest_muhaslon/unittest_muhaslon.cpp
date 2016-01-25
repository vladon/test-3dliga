#include <gtest/gtest.h>
#include <tools.h>
#include <muhaslon.h>

TEST(TestWordDistance, Test1)
{
    EXPECT_EQ(WordDistance(L"люкн", L"лшкн"), 1);
}

TEST(TestWordDistance, Test0)
{
    EXPECT_EQ(WordDistance(L"люлю", L"люлю"), 0);
}

TEST(TestWordDistance, TestInf)
{
    EXPECT_EQ(WordDistance(L"якнм", L"люлнмр"), std::numeric_limits<size_t>::max());
}

TEST(TestWordDistance, TestEmpty)
{
    EXPECT_EQ(WordDistance(L"", L""), 0);
}

TEST(TestMuhaSlon, Test1)
{
    std::vector<std::wstring> Dictionary{};
    MuhaSlon Test1{ Dictionary };
    std::vector<std::wstring> ExpectedRes{ L"лсую" };

    EXPECT_EQ(Test1.GetPath(L"лсую", L"лсую"), ExpectedRes);
}

TEST(TestMuhaSlon, Test0)
{
    std::vector<std::wstring> Dictionary{};
    MuhaSlon Test0{ Dictionary };
    std::vector<std::wstring> ExpectedRes{};

    EXPECT_EQ(Test0.GetPath(L"лсую", L"якнм"), ExpectedRes);
}

TEST(TestMuhaSlon, TestEthalon)
{
    std::vector<std::wstring> Dictionary{
        L"йнр",
        L"рнм",
        L"мнрю",
        L"йнрш",
        L"пнр",
        L"пнрю",
        L"рнр"
    };

    MuhaSlon TestEthalon{ Dictionary };
    std::vector<std::wstring> ExpectedRes{ L"йнр", L"рнр", L"рнм" };

    EXPECT_EQ(TestEthalon.GetPath(L"йнр", L"рнм"), ExpectedRes);
}
