#include "minish.h"

int print_information(char *name_of_file){ //Imprime la información del archivo
    char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    struct passwd *pwd = malloc(sizeof(struct passwd)*100);
    struct stat file_stat;  
    int ret = stat(name_of_file, &file_stat); 
    pwd = getpwuid(file_stat.st_uid);
    char* name_files = pwd->pw_name;
    struct tm* clock;
    clock = gmtime(&(file_stat.st_ctime));
    int ngroups = getgroups (0, NULL);
    gid_t *groups = (gid_t *) malloc (ngroups * sizeof (gid_t));
    struct group *grp;
    int val = getgroups (ngroups, groups);
    grp = getgrgid(groups[0]);
    if(pwd == NULL || val == 0){
        error(0, errno, "Falla al leer la información del archivo\n");
        return 1;
    }
    else{
        printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
        printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
        printf("  %-15s %-15s %-7ld  %-7ld  %10s %-2d %-30s\n",pwd->pw_name,grp->gr_name,file_stat.st_size,file_stat.st_ino, months[clock->tm_mon],clock->tm_mday,name_of_file);
    }

    return 0;
}

int traverse_list(char **list_of_names, int size){ //Recorre la lista ordenada
    for(int index = 0; index < size; index++){
        if(print_information(list_of_names[index]) == 1){
            return 1;
        }
    }
    return 0;
}

int sort(char **list_of_name, int size){ //Ordena la listaa
    for(int first_index=0; first_index < size-1; first_index++){
        for(int second_index = first_index + 1; second_index < size; second_index++){
            if(strcmp(list_of_name[first_index], list_of_name[second_index]) > 0){
                char* temp = list_of_name[first_index];
                list_of_name[first_index] = list_of_name[second_index];
                list_of_name[second_index] = temp;
            }
        }
    }
    return traverse_list(list_of_name, size);
}

int search_directory(char *name){ //Buscar en el directorio cada archivo
    char** list_names = malloc(sizeof(char*)*100);
    int size_of_list = 0;
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name);
    if(pDirectorio == NULL){
        error(0, errno, "Directorio inválido\n");
        return 1;
    }
    while((dir = readdir(pDirectorio))!= NULL){
        char* name_file = malloc(sizeof(char)*100);
        name_file = dir->d_name;
        list_names[size_of_list] = name_file;
        size_of_list++;
    }
    closedir(pDirectorio);
    return sort(list_names, size_of_list); 
}
int search_with_filter(char *name, char*filtro){ //Busca en el directorio con el filtro correspondiente
    char** list_names = malloc(sizeof(char*)*100);
    int size_of_list = 0;
    struct dirent *dir;
    DIR *pDirectorio;
    pDirectorio = opendir(name);
    dir = readdir(pDirectorio);
    if(pDirectorio == NULL){
        error(0, errno, "Directorio inválido\n");
        return 1;
    }
    while((dir = readdir(pDirectorio))!= NULL) {
        if(strstr(dir->d_name, filtro)){
            char* name_file = malloc(sizeof(char)*100);
            name_file = dir->d_name;
            list_names[size_of_list] = name_file;
            size_of_list++;
        }
    }
    closedir(pDirectorio);
    return sort(list_names, size_of_list); 
}
int type_of_file(char *name){ //Define el tipo de archivo  que es
    struct stat file_stat;  
    int ret = stat(name, &file_stat);
    if(ret < 0){
        return search_with_filter(".",name);
    }
    else if(S_ISREG(file_stat.st_mode)){
        return print_information(name);
    }else{
        return search_directory(name);
    }
    return 0;
}
int builtin_dir(int argc, char ** argv){


    if(argc == 1){
        search_directory(".");
    }
    else if(argc == 2){
        return type_of_file(argv[1]); //ARREGLAR
        
    }
    else if(argc == 3){
        return search_with_filter(argv[1],argv[2]);
        
    }
    else{
        error(0, errno, "Muchos argumentos\n"); // will fprintf the error and go on
        return 1;
    }
    return 0;
}