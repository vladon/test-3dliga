#pragma once

#include <codecvt>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void ShowUsage();

std::wstring string_to_wstring(const std::string & source);

size_t WordDistance(const std::wstring & Word1, const std::wstring & Word2);

void DumpWStringVectorToConsole(const std::vector<std::wstring> & vec);

std::vector<std::wstring> LoadLinesFromFile(const char * const Filename, size_t LinesLimit = std::numeric_limits<size_t>::max());
