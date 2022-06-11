#include "builtin.h"

int builtin_setenv(int argc, char **argv){
    if (argc > 2){
        if (setenv(argv[1], argv[2], 1) == -1){
            perror("setenv");
            return errno;
        }
    }
    return 0;
}