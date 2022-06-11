#include "minish.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int externo (int argc, char **argv) {
    /*

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

            execvp(argv[0],argv);
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
    */
}