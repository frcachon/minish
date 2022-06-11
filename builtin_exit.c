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

    if (argc == 1) { // solo comando
        exit(globalstatret);
        return globalstatret;
    }

    else if(argc == 2) { // comando con parametro
        if (isdigit(argv[1]) == 1) { // chequeo si el parametro es numerico
            exit(argv[1]);
            return argv[1];
        } else { // si no es numerico, error
            return -1;
        }
    }

    else {
        return -1;
    }

}