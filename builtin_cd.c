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
        if (setenv(OLDPWD, cwd, 1) == -1){
            //aca va el error
        }
        if ((home = getenv(HOME)) == NULL){
            //aca va el error
        }
        status = chdir(home); 
    }
    else if (strcmp(argv[1], "-") == 0) {
        if ((oldpwd = getenv(OLDPWD)) == NULL){
            //aca va el error
        }
        if ((status = chdir(oldpwd)) == -1){
            //aca va el error
        }
        printf("%s\n", oldpwd);             
        if (setenv("OLDPWD", cwd, 1) == -1){
            //aca va el error
        }
    }
    else{
        if (setenv("OLDPWD", cwd, 1) == -1){
            //aca va el error
        }
        status = chdir(argv[1]);
    }
    if (status != 0)
        perror("cd");
    return status;
}