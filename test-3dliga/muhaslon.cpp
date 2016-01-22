#include "muhaslon.h"

MuhaSlon::MuhaSlon(const char * const DictionaryFilename)
{
    LoadDictionary(DictionaryFilename);
}

void MuhaSlon::LoadDictionary(const char * const DictionaryFilename)
{
    Dictionary_ = LoadLinesFromFile(DictionaryFilename);

    std::sort(Dictionary_.begin(), Dictionary_.end());
    std::unique(Dictionary_.begin(), Dictionary_.end());
}

std::vector<std::wstring> MuhaSlon::GetPath(const std::wstring & WordFrom, const std::wstring & WordTo) const
{
    std::vector<std::wstring> Result;

    // Из пустого слова в пустое слово - пустой путь
    if (WordFrom.empty() || WordTo.empty())
    {
        return Result;
    }

    // Если длина слов не совпадает, то пути нет (пустой)
    if (WordFrom.size() != WordTo.size())
    {
        return Result;
    }

    // Из слова в самого себя - путь из самого себя
    if (WordFrom == WordTo)
    {
        Result.push_back(WordFrom);
        return Result;
    }

    // Если слова отличаются только на одну букву, то они и есть путь
    if (WordDistance(WordFrom, WordTo) == 1)
    {
        Result.push_back(WordFrom);
        Result.push_back(WordTo);
        return Result;
    }

    //
    // Начинаем искать путь
    //

    auto WordLength = WordFrom.size();

    // Формируем словарь только подходящих по длине слов
    std::list<std::wstring> TempDictionary{};
    std::copy_if(Dictionary_.begin(), Dictionary_.end(), std::back_inserter(TempDictionary), [WordLength](const std::wstring & ws)
    {
        return ws.size() == WordLength;
    });

    // Очередь из слов
    std::deque<std::shared_ptr<TransitionWord>> TransitionWords;

    // Начинаем с мухи
    auto CurrentWordPtr = std::make_shared<TransitionWord>(WordFrom);
    TransitionWords.push_back(CurrentWordPtr);

    // Перебираем слова из словаря по очереди
    // Если нашли отличающееся на 1 букву слово, то записываем в нашу очередь
    // Если нет - пропускаем
    // Если слово не будет подобрано, то последнее слово из очереди будет удалено при входе в цикл
    while (!TransitionWords.empty())
    {
        CurrentWordPtr = TransitionWords.front();
        TransitionWords.pop_front();

        // Дошли до слона - ура
        if (CurrentWordPtr->Value_ == WordTo)
        {
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

    // Копируем слова из полученной очереди в результат
    if (CurrentWordPtr->Value_ == WordTo)
    {
        std::list<std::wstring> ReverseResult;
        while (CurrentWordPtr != nullptr)
        {
            ReverseResult.push_back(CurrentWordPtr->Value_);
            CurrentWordPtr = CurrentWordPtr->Prev_;
        }
        Result.assign(ReverseResult.rbegin(), ReverseResult.rend());
    }

    return Result;
}
