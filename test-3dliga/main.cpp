#include <iostream>
#include <string>

#include "tools.h"
#include "muhaslon.h"

int main(int argc, char ** argv)
{
    if (argc < 3)
    {
        ShowUsage();
        return 1;
    }

    MuhaSlon LocalMuhaSlon(argv[1]);

    auto Words = LoadLinesFromFile(argv[2], 2);
    auto Res = LocalMuhaSlon.GetPath(Words[0], Words[1]);
    DumpWStringVectorToConsole(Res);
    
    return 0;
}
