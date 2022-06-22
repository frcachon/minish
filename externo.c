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

int externo (__attribute__((unused)) int argc, char **argv) {

    pid_t pid,w;                          // process ID: an unsigned integer type
    int wait_status;                    // wait status will be filled by waitpid syscall

    sigaction(SIGINT, NULL, &oldact);   // the  previous action for SIGINT is saved in oldact
    newact = oldact;

    if ((pid = fork()) < 0) {           // fork error, i.e. too many processes
        error(0, errno, "fork error\n"); // will fprintf the error and go on
    }

    else if (pid == 0) {                 // child process
        
        newact.sa_handler = SIG_DFL;
        sigaction(SIGINT, &newact, NULL);   // reset SIGINT default for child

        execvp(argv[0],argv);
        //execlp("sleep", "sleep", "5", NULL);    // if successful, child will go on with new executable
        error(EXIT_FAILURE, errno, "execvp error\n"); // if exec not successful, just exit child
    }

    else {                               // pid > 0: parent (shell) process

        newact.sa_handler = SIG_IGN;
        sigaction(SIGINT, &newact, NULL);   // ignore SIGINT while waiting

        w = waitpid(pid, &wait_status, 0);

        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(wait_status)) {
            return(WEXITSTATUS(wait_status));
        } else if (WIFSIGNALED(wait_status)) {
            return(WTERMSIG(wait_status));
        }

        sigaction(SIGINT, &oldact, NULL);   // restore SIGINT when child finishes

        // do something with wait_status

    }
    return 1;
}