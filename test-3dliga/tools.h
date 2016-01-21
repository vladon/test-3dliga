#pragma once

#include <iostream>
#include <string>

void ShowUsage();

std::wstring string_to_wstring(const std::string & source);

template <typename WordT = std::string>
size_t WordDistance(const WordT & Word1, const WordT & Word2)
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
