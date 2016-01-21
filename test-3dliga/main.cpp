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

    MuhaSlon LocalMuhaSlon(argv[2]);
    
    return 0;
}

