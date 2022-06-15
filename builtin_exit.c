// usando void exit(int status) syscall

// The function _exit() terminates the calling process "immediately". Any open file descriptors
// belonging to the process are closed; any children of the process are inherited by process 1,
// init, and the process's parent is sent a SIGCHLD signal.
// The value status is returned to the parent process as the process's exit status, and can be
// collected using one of the wait(2) family of calls.

#include "minish.h"
#include <stdlib.h>
#include <ctype.h>

int builtin_exit(int argc, char ** argv) {

    if (argc == 1) { // solo comando (sin parametro)
        exit(globalstatret); // llamo al sistema
        return globalstatret; // retorno el status global
    }

    else if(argc == 2) { // comando con parametro
    int new_status = *strdup(argv[1]);
        if (new_status != 0) { // chequeo si el parametro es numerico
            exit(new_status); // segun la letra, debo llamar al sistema con el estado pasado por parametro
            return new_status; // y tambien retorno ese estado
        } else { // si el parametro no es numerico, error
            error(EXIT_SUCCESS, 0, "El parametro no es numerico.");
            return 1;
        }
    }

    else {
        error(EXIT_SUCCESS, 0, "Solo se admite un parametro.");
        return 1; // para otro caso (multiples parametros), retorno error
    }

}