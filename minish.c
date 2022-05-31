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

#define MAXLINE 1024
#define MAXWORDS 256

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