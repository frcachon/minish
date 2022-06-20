#include "minish.h"

void es_File(char *name){ //Abrimos la informacion del archivo regulable
    struct stat file_stat;  
    int ret = stat(name, &file_stat); 
    printf("%25s       %9ld       %9s \n",name,file_stat.st_ino, getpwuid(file_stat.st_uid)->pw_name);
}

int es_Dir(char *name){ //El archivo es directorio, por ende se debe imprimir toda la informacion de cada uno de los archivos dentro. 
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name); //Abrimos el directorio
    if(pDirectorio == NULL) { //Error al abrir el directorio
        error(0, errno, "Directorio inválido\n");
        return 1;
    }
    while((dir = readdir(pDirectorio))!= NULL) { //Vamos leyendo cada archivo dentro
        es_File(dir->d_name);
    }
    closedir(pDirectorio); //Cerramos el directorio
    return 0; 
}

int con_Filtro(char *name, char*filtro) { //Recibe el directorio y el filtro para obtener los archivos dentro
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name);
    if(pDirectorio == NULL){
        error(0, errno, "Directorio inválido\n");
        return 1;
    }
    while((dir = readdir(pDirectorio))!= NULL) {
        if(strstr(dir->d_name, filtro)){
            es_File(dir->d_name);
        }
    }
    closedir(pDirectorio);
    return 0; 
}

int tipo_Archivo(char *name) { //Se verifica que tipo de archivo es
    
    struct stat file_stat;  
    int ret = stat(name, &file_stat);
    if(ret < 0) { //Tomamos el directorio corriente y buscamos dentro los archivos regulables que tengan las letras que estan en el name
        return con_Filtro(".",name);
    }
    else if(S_ISREG(file_stat.st_mode)) { //Verificamos si es un archivo regular
        printf("%25s       %9ld       %9s \n",name,file_stat.st_ino, getpwuid(file_stat.st_uid)->pw_name); //Si lo es, imprimimos la información.
        return 0;
    }else { //Si no lo es, lo tomamos como directorio
        return es_Dir(name);
    }
}

int builtin_dir(int argc, char ** argv) {
    if(argc == 1) { //Si no obtenemos nada, tomamos el archivo corriente
        return es_Dir(".");
    }
    else if(argc == 2) { //Si obtenemos un solo argumento, puede ser un directorio o un archivo regular
        return tipo_Archivo(argv[1]); 
        
    }
    else if(argc == 3) { //Si obtenemos 2 argumentos, es un directorio y el filtro para obtener los archivos regulables
        return con_Filtro(argv[1],argv[2]);
        
    }
    else {
        error(0, errno, "Muchos argumentos\n"); 
        return 1;
    }
}