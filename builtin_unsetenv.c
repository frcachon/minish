#include "builtin.h"

int builtin_unsetenv(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
        unsetenv(argv[i]);
    return 0;
}