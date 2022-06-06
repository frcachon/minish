#include "minish.h"


int builtin_cd (int argc, char ** argv){
    char cwd[MAXCWD], *home, *oldpwd;
    int status;
    if (getcwd(cwd, sizeof(cwd)) == NULL){
        //aca va el erro
    }
    else if (argc > 2){
        printf("minish: %s: Demasiados argumentos\n", argv[0]);
        return -1;
    }
    else if (argc == 1) {
        status = chdir(home); 
    }
    else if (strcmp(argv[1], "-") == 0) {
        
    }
    else{
        status = chdir(argv[1]);
    }
    if (status != 0)
        perror("cd");
    return status;
}