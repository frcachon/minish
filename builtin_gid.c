#include "minish.h"

int builtin_gid(){
    int ngroups = getgroups (0, NULL); //Obtengo la cantidad de grupos
    gid_t *groups = (gid_t *) malloc (ngroups * sizeof (gid_t)); //Creo un array de tamaño ngroups
    struct group *grp;
    int val = getgroups (ngroups, groups); //Obtengo los grupos y los guardo en el array previamente creado
    if(val < 0){
        error(0, errno, "Error al obtener los grupos\n");
        return 1;
    }
    printf("%s","groups=");
    for(int i=0; i<val; i++){
        if(i == val - 1){ //Esta opción es para que el ultimo no tenga coma al final. 
            grp = getgrgid(groups[i]);
            printf("%d(%s)",groups[i], grp->gr_name);
        }
        else{
            grp = getgrgid(groups[i]);
            printf("%d(%s),",groups[i], grp->gr_name);
        }
    }
    return 1;
}