#include "minish.h"

int builtin_getenv(int argc, char ** argv){
    char *pTmp = malloc(sizeof(char*)*200);
    if(argc>1){
        for(int i=1; i < argc; i++){
            if (( pTmp =getenv(argv[i])) != NULL ){ 
            printf("%s = %s\n", argv[i],pTmp);
            } else{
                error(0, errno, "No se encontró la variable\n");
                return 1;        
            }
        }
        return 0;
    }else{
        
    }
}