#pragma once

#include <algorithm>
#include <codecvt>
#include <deque>
#include <fstream>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "tools.h"


class MuhaSlon
{
public:
    explicit MuhaSlon(const char * const DictionaryFilename);

    void LoadDictionary(const char * const DictionaryFilename);

    std::vector<std::wstring> GetPath(const std::wstring & WordFrom, const std::wstring & WordTo) const;

private:
    std::vector<std::wstring> Dictionary_;

    class TransitionWord
    {
    public:
        explicit TransitionWord(std::wstring Word)
            : Value_(Word)
        {
        }

        std::shared_ptr<TransitionWord> Prev_{ nullptr };
        std::wstring Value_;
    };
};
