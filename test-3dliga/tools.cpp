#include "tools.h"

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
