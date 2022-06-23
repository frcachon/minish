#include "minish.h"

int builtin_cd (int argc, char ** argv) {
    char cwd[MAXCWD], *home, *oldpwd;
    int status;
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("cd");
        return errno;
    }
    else if (argc > 2) { // no puede ser mayor a 2 porque admito, como maximo, 1 parametro
        printf("minish: %s: Demasiados argumentos\n", argv[0]);
        return -1;
    }
    else if (argc == 1) { // linea: "cd"
        if ((home = getenv(HOME)) == NULL) {
            perror("cd");
            return errno;
        }
        status = chdir(home);
    }
    else if (strcmp(argv[1], "-") == 0) {
        if ((oldpwd = getenv(OLDPWD)) == NULL) { // Obtengo el valor de $OLDPWD
            perror("cd");
            return errno;
        }
        if ((status = chdir(oldpwd)) == -1) { // Cambio al directorio anterior al actual
            perror("cd");
            return errno;
        }

        printf("%s\n", oldpwd);
        if (setenv("OLDPWD", cwd, 1) == -1) { // Guardo el directorio, ahora anterior, en $OLDPWD
            perror("cd");
            return errno;
        }
    }
    else {
        if (setenv("OLDPWD", cwd, 1) == -1) { // linea: "cd xxx". Este tambien guarda la posicion anterior
            perror("cd");
            return errno;
        }
        status = chdir(argv[1]);
    }
    if (status != 0)
        perror("cd");
    return status;
}