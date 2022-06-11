#include "minish.h"

void builtin_getenv(int argc, char ** argv){
    char *pTmp = malloc(sizeof(char*)*200);

    for(int i=0; i < argc; i++){
        if (( pTmp =getenv(argv[i])) != NULL ){
        printf("%s = %s\n", argv[i],pTmp);
        } else{
            error(0, errno, "No se encontró la variable\n");        
        }
    }
}