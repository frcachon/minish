#include "minish.h"
#include "builtin.h"

int globalstatret = 0;
struct sigaction oldact;
struct sigaction newact;

void print_prompt() {
   char cwd[1028];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       fprintf(stderr, "%s> ", cwd);
   } else {
       error(0, errno, "Error al obtener el path\n");
   }
}

void sigint_handler(int ssignum) { // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", ssignum);
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    char *palabras[MAXWORDS];
    
    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    char *res;
    int cantidad_de_palabras;

    for (;;) {
        print_prompt();

        res = fgets(line, MAXLINE, stdin);
        cantidad_de_palabras = linea2argv(line, MAXWORDS, palabras);

        if (res != NULL && cantidad_de_palabras > 0){
            ejecutar(cantidad_de_palabras, palabras);
        }

    }

}