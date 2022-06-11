#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#define MAXLINE 1024        // tamaño máximo de la línea de entrada
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

// esto es nomas para que no de error
int builtin_dir(int argc, char ** argv) {
    return 0;
}
//

void es_File(char *name){
    struct stat file_stat;  
    int ret = stat(name, &file_stat); 
    printf("%25s       %9ld       %9s \n",name,file_stat.st_ino, getpwuid(file_stat.st_uid)->pw_name);
}

int es_Dir(char *name){
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name);
    if(pDirectorio == NULL){
        error(0, errno, "Directorio inválido\n");
        return -1;
    }
    while((dir = readdir(pDirectorio))!= NULL){
        es_File(dir->d_name);
    }
    closedir(pDirectorio);
    return 1; 
}
int con_Filtro(char *name, char*filtro){
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name);
    if(pDirectorio == NULL){
        error(0, errno, "Directorio inválido\n");
        return -1;
    }
    while((dir = readdir(pDirectorio))!= NULL){
        if(strstr(dir->d_name, filtro)){
            es_File(dir->d_name);
        }
    }
    closedir(pDirectorio);
    return 1; 
}

int tipo_Archivo(char *name){
    struct stat file_stat;  
    int ret = stat(name, &file_stat);
    if(ret < 0){
        printf("%s", "ENTRO");
        return con_Filtro(".",name);
    }
    else if(S_ISREG(file_stat.st_mode)){
        printf("%25s       %9ld       %9s \n",name,file_stat.st_ino, getpwuid(file_stat.st_uid)->pw_name);
        return 1;
    }else{
        return es_Dir(name);
    }
}