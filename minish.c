#include "minish.h"
#include "builtin.h"

int globalstatret = 0;

void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

// ============== NEW CODE HERE ==============
void
sigint_handler(int ssignum) {                    // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", ssignum);
}

int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    struct sigaction newact;

    char *palabras[MAXWORDS];
    
    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    char *res;

    for (;;) {
        prompt(progname);
        //if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
          //  if (feof(stdin)) {
            //    break;      // normal EOF, break loop
            //} else {
             //   continue;   // not EOF, read system call was interrupted, continue loop
           // }
        //}

        //int cantidad_de_palabras = linea2argv(line, MAXWORDS, palabras); // parseo de linea ingresada en prompt

        //int status_externo = externo(MAXWORDS, palabras); // para comandos externos

        res = fgets(line, MAXLINE, stdin);

        int cantidad_de_palabras = linea2argv(line, MAXWORDS, palabras);
        if (res != NULL && cantidad_de_palabras > 0){
            ejecutar(cantidad_de_palabras, palabras);
        }
    }

}