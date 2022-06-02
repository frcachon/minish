#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
#include <stdbool.h>

#include "minish.h"

#define HELP_CD      "cd [..|dir] - cambia de directorio corriente"
#define HELP_DIR     "dir [str]- muestra archivos en directorio corriente, que tengan 'str'"
#define HELP_EXIT    "exit [status] - finaliza el minish con un status de retorno (por defecto 0)"
#define HELP_HELP    "help [cd|dir|exit|help|history|getenv|pid|setenv|status|uid]"
#define HELP_HISTORY "history [N] - muestra los últimos N (10) comandos escritos"
#define HELP_GETENV  "getenv var [var] - muestra valor de variable(s) de ambiente"
#define HELP_PID     "pid - muestra Process Id del minish"
#define HELP_SETENV  "setenv var valor - agrega o cambia valor de variable de ambiente"
#define HELP_STATUS  "status - muestra status de retorno de ultimo comando ejecutado"
#define HELP_UID     "uid - muestra nombre y número de usuario dueño del minish"

// struct builtin_struct builtin_arr[] = {
//     { "cd", builtin_cd, HELP_CD },
//     { "dir", builtin_dir, HELP_DIR },
//     { "exit", builtin_exit, HELP_EXIT },
//     { "help", builtin_help, HELP_HELP },
//     { "history", builtin_history, HELP_HISTORY },
//     { "getenv", builtin_getenv, HELP_GETENV },
//     { "pid", builtin_pid, HELP_PID },
//     { "setenv", builtin_setenv, HELP_SETENV },
//     { "status", builtin_status, HELP_STATUS },
//     { NULL, NULL, NULL }
// };

void
prompt(char *ps) {
    // ps is the prompt string
    fprintf(stderr, "(%s) ^D to exit > ", ps);
}

// ============== NEW CODE HERE ==============
void
sigint_handler(int signum) {                    // the handler for SIGINT
    fprintf(stderr, "Interrupt! (signal number %d)\n", signum);
}

int
main(int argc, char *argv[]) {
    char line[MAXLINE];
    char *progname = argv[0];
    struct sigaction oldact, newact;

    char *palabras[MAXWORDS];
    
    sigaction(SIGINT, NULL, &newact);           // the  previous action for SIGINT is saved in oldact
    newact.sa_handler = sigint_handler;
    sigaction(SIGINT, &newact, NULL);           // set SIGINT handler for loop


    for (;;) {
        prompt(progname);
        if (fgets(line, MAXLINE, stdin) == NULL) {  // EOF
            // ============== NEW CODE HERE ==============
            if (feof(stdin)) {
                break;      // normal EOF, break loop
            } else {
                continue;   // not EOF, read system call was interrupted, continue loop
            }
        }

        //fprintf(stderr, "Will execute command %s", line);

        int cantidad_de_palabras = linea2argv(line, MAXWORDS, palabras);

        pid_t pid;                          // process ID: an unsigned integer type
        int wait_status;                    // wait status will be filled by waitpid syscall

        sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
        newact = oldact;

        if ((pid = fork()) < 0) {           // fork error, i.e. too many processes
            error(0, errno, "fork error\n"); // will fprintf the error and go on
        }

        else if (pid == 0) {                 // child process
            
            // ============== NEW CODE HERE ==============
            newact.sa_handler = SIG_DFL;
            sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child

            execvp(palabras[0],palabras);
            //execlp("sleep", "sleep", "5", NULL);    // if successful, child will go on with new executable
            error(EXIT_FAILURE, errno, "execvp error\n"); // if exec not successful, just exit child
        }

        else {                               // pid > 0: parent (shell) process

            // ============== NEW CODE HERE ==============
            newact.sa_handler = SIG_IGN;
            sigaction(SIGINT, &newact, NULL);   // ignore SIGINT while waiting

            waitpid(pid, &wait_status, 0);

            // ============== NEW CODE HERE ==============
            sigaction(SIGINT, &oldact, NULL);   // restore SIGINT when child finishes

            // do something with wait_status
            
        }
    }

    fputc('\n', stderr);
    fprintf(stderr, "Exiting %s ...\n", progname);
    exit(EXIT_SUCCESS);
}