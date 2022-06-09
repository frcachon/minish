// using void exit(int status) syscall

// The function _exit() terminates the calling process "immediately". Any open file descriptors
// belonging to the process are closed; any children of the process are inherited by process 1,
// init, and the process's parent is sent a SIGCHLD signal.

// The value status is returned to the parent process as the process's exit status, and can be
// collected using one of the wait(2) family of calls.

int builtin_exit() {
    exit(globalstatret)
    return globalstatret;
}