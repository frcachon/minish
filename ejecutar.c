#include "minish.h"
#include "builtin.h"

int ejecutar(int argc, char **argv) {
    
    struct builtin_struct *matched_struct = NULL;

    // comandos internos:
    if ((matched_struct = builtin_lookup(argv[0])) != NULL)
        globalstatret = matched_struct->func(argc, argv); // Guarda el valor de retorno de cada comando interno ejecutado.
    
    // comandos externos:
    else
        globalstatret = externo(argc, argv); // Guarda el valor de retorno de cada comando externo ejecutado.

    return globalstatret;
}