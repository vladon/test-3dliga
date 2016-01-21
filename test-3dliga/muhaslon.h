#pragma once

#include <deque>
#include <fstream>
#include <string>
#include <list>
#include <memory>
#include <vector>

#include "tools.h"

using WordT = std::string;

class MuhaSlon
{
public:
    explicit MuhaSlon(const char * const DictionaryFilename)
    {
        LoadDictionary(DictionaryFilename);
    }

    void LoadDictionary(const char * const DictionaryFilename)
    {
        if (!Dictionary_.empty())
        {
            Dictionary_.clear();
        }

        std::ifstream DictionaryFile(DictionaryFilename);
        if (!DictionaryFile.is_open())
        {
            throw std::runtime_error("Cannot open specified dictionary file.");
        }

        for (std::string line; std::getline(DictionaryFile, line); )
        {
            Dictionary_.push_back(line);
        }

        Dictionary_.sort();
        Dictionary_.unique();
    }

    std::vector<WordT> GetPath(const WordT & WordFrom, const WordT & WordTo) const
    {
        std::vector<std::string> Result;

        if (WordFrom.empty() || WordTo.empty())
        {
            return Result;
        }

        if (WordFrom == WordTo)
        {
            Result.push_back(WordFrom);
            return Result;
        }

        if (WordDistance(WordFrom, WordTo) == 1)
        {
            Result.push_back(WordFrom);
            Result.push_back(WordTo);
            return Result;
        }

        auto TempDictionary{ Dictionary_ };
        auto WordLength = WordFrom.size();
        TempDictionary.remove_if([WordLength](const WordT & Word)
        {
            return Word.size() != WordLength;
        });

        std::deque<std::shared_ptr<TransitionWord>> TransitionWords;
        std::shared_ptr<TransitionWord> CurrentWordPtr = std::make_shared<TransitionWord>(WordFrom);
        TransitionWords.push_back(CurrentWordPtr);
        while (!TransitionWords.empty())
        {
            CurrentWordPtr = TransitionWords.front();
            TransitionWords.pop_front();

            if (CurrentWordPtr->Value_ == WordTo)
            {
                TransitionWords.clear();
                TempDictionary.clear();
                break;
            }

            auto it = TempDictionary.begin();
            while (it != TempDictionary.end())
            {
                auto diff = WordDistance(CurrentWordPtr->Value_, *it);
                if (diff == 1)
                {
                    TransitionWords.push_back(std::make_shared<TransitionWord>(*it));
                    TransitionWords.back()->Prev_ = CurrentWordPtr;
                    TempDictionary.erase(it++);
                    continue;
                }
                ++it;
            }
        }

        if (CurrentWordPtr->Value_ == WordTo)
        {
            std::list<WordT> ReverseResult;
            while (CurrentWordPtr != nullptr)
            {
                ReverseResult.push_back(CurrentWordPtr->Value_);
                CurrentWordPtr = CurrentWordPtr->Prev_;
            }
            Result.assign(ReverseResult.rbegin(), ReverseResult.rend());
        }

        return Result;
    }

private:
    std::list<WordT> Dictionary_;

    class TransitionWord
    {
    public:
        explicit TransitionWord(WordT Word)
            : Value_(Word)
        {
        }

        std::shared_ptr<TransitionWord> Prev_{ nullptr };
        WordT Value_;
    };

};
