#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <stdbool.h>
#include <ctype.h>


#define MAXLINE 1024                   // tamaño máximo de la línea de entrada
#define MAXCWD 1024                    // tamaño máximo para alojar el pathname completo del directorio corriente
#define MAXWORDS 256                   // cantidad máxima de palabras en la línea
#define HISTORY_FILE ".minish_history"

#define HOME "HOME"
#define OLDPWD "OLDPWD"

// Variables
extern int globalstatret; // guarda status del ultimo comando - deberá definirse en el main
extern struct sigaction oldact;
extern struct sigaction newact;

// Funciones
extern int ejecutar(int argc, char **argv);
extern int externo(int argc, char **argv);
extern int linea2argv(char *linea, int argc, char **argv);
extern void print_prompt();         // imprime el prompt string
extern void append_history(char *); // registra el comando ejecutado en el archivo ~/.minish_history