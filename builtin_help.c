#include "minish.h"
#include "builtin.h"
#include <stdlib.h>

int builtin_help(int argc, char ** argv){

    struct builtin_struct *builtin_st = NULL;

    if (argc == 1) {
        for (builtin_st = builtin_arr; builtin_st -> cmd != NULL; builtin_st++) {
            printf("%s\n",builtin_st -> help_txt);
        }
        return 0;
    }

    else if(argc == 2) {
        builtin_st = builtin_lookup(argv[1]);
        if (builtin_st != NULL){
            printf("%s\n",builtin_st -> help_txt);
            return 0;
        }
        else {
            printf("Comando no encontrado.\n");
            return -1;
        }
    }

    else {
        return -1;
    }

}