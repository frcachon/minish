#include "minish.h"
#include "builtin.h"

int globalstatret = 0;
struct sigaction oldact;
struct sigaction newact;

void print_prompt() { // funcion sin parametros que se encarga de imprimir la linea del prompt
   char cwd[1028];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       fprintf(stderr, "%s> ", cwd); // obtengo el path y lo imprimo
   } else {
       error(0, errno, "Error al obtener el path\n");
   }
}

void sigint_handler(int ssignum) { // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", ssignum); // aviso en caso de recibir una
}                                                                // interrupcion por teclado

void append_history(char *line)
{
    char *home, minish_history_dir[MAXCWD];
    FILE *f;
    int ano, mes, dia, hora, min, seg;
    time_t ahora;
    struct tm *local;

    home = getenv("HOME");
    snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
    f = fopen(minish_history_dir, "a");
    if (f != NULL){
        time(&ahora);
        local = localtime(&ahora);
        ano = local->tm_year + 1900;
        mes = local->tm_mon + 1;
        dia = local->tm_mday;
        hora = local->tm_hour;
        min = local->tm_min;
        seg = local->tm_sec;

        fprintf(f, "%02d-%02d-%04d\t%02d:%02d:%02d\t%s", dia, mes, ano, hora, min, seg, line);
        fclose(f);
    }
}

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    char *palabras[MAXWORDS]; // la estructura equivalente a argv[]
    
    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop

    char *res;
    int cantidad_de_palabras; // entero equivalente a argc

    for (;;) {
        print_prompt();

        res = fgets(line, MAXLINE, stdin);// recibo una linea a traves del prompt
        append_history(line);
        cantidad_de_palabras = linea2argv(line, MAXWORDS, palabras);// parseo la linea y almaceno en palabras

        if (res != NULL && cantidad_de_palabras > 0){
            ejecutar(cantidad_de_palabras, palabras); // invoco funcion ejecutar para que busque el comando
        }                                             // (sea un builtin o no)

    }

}