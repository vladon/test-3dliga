#include "tools.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif // _WIN32

#include <algorithm>

void ShowUsage()
{
    std::cout <<
        "Parameters:\n"
        "\t[WordsFile] [DictionaryFile]" << std::endl;
}

std::wstring string_to_wstring(const std::string & source)
{
    return std::wstring(source.begin(), source.end());
}

size_t WordDistance(const std::wstring & Word1, const std::wstring & Word2)
{
    if (Word1 == Word2)
    {
        return 0;
    }

    if (Word1.size() != Word2.size())
    {
        return std::numeric_limits<size_t>::max();
    }

    size_t result{ 0 };
    for (size_t i = 0; i < Word1.size(); ++i)
    {
        if (Word1[i] != Word2[i])
        {
            ++result;
        }
    }

    return result;
}

void DumpWStringVectorToConsole(const std::vector<std::wstring> & vec)
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
#endif
    std::for_each(vec.begin(), vec.end(), [](const std::wstring & ws)
    {
        std::wcout << ws << std::endl;
    });
}

std::vector<std::wstring> LoadLinesFromFile(const char * const Filename, size_t LinesLimit)
{
    std::vector<std::wstring> Result;

    using ConverterType = std::codecvt_utf8<wchar_t>;
    ConverterType * Converter = new ConverterType(); // будет освобождён деструктором Utf8Locale
    const auto EmptyLocale{ std::locale::empty() };
    const auto Utf8Locale = std::locale(EmptyLocale, Converter);
    std::wifstream Stream(Filename);
    if (!Stream.is_open())
    {
        throw std::runtime_error("Cannot open specified dictionary file.");
    }
    Stream.imbue(Utf8Locale);

    size_t LinesCounter = 0;
    std::wstring line;
    while (std::getline(Stream, line) && LinesCounter < LinesLimit)
    {
        Result.push_back(line);
    }

    return Result;
}
