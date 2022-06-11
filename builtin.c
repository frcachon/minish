#include "builtin.h"

/*
struct builtin_struct builtin_arr[] = {
    {"cd", builtin_cd, HELP_CD},                        hecho
    {"dir", builtin_dir, HELP_DIR},                     hecho
    {"exit", builtin_exit, HELP_EXIT},                  hecho
    {"help", builtin_help, HELP_HELP},                  hecho
    {"history", builtin_history, HELP_HISTORY},
    {"getenv", builtin_getenv, HELP_GETENV},            hecho
    {"pid", builtin_pid, HELP_PID},                     hecho
    {"gid", builtin_gid, HELP_GID},
    {"setenv", builtin_setenv, HELP_SETENV},            
    {"unsetenv", builtin_unsetenv, HELP_UNSETENV},
    {"status", builtin_status, HELP_STATUS},            hecho
    {"uid", builtin_uid, HELP_UID},
    {NULL, NULL, NULL}};
*/

struct builtin_struct builtin_arr[] = {
    {"cd", builtin_cd, HELP_CD},
    {"dir", builtin_dir, HELP_DIR},
    {"exit", builtin_exit, HELP_EXIT},
    {"help", builtin_help, HELP_HELP},
    {"status", builtin_status, HELP_STATUS},
    {NULL, NULL, NULL}
};

struct builtin_struct *builtin_lookup(char *cmd) {   // es para recorrer builtin_arr

    struct builtin_struct *builtin_struct_ptr = NULL;
    builtin_struct_ptr = builtin_arr;

    while (builtin_struct_ptr->cmd != NULL) {
        if (strcmp(cmd, builtin_struct_ptr->cmd) == 0) 
            return builtin_struct_ptr;
        builtin_struct_ptr++;
    }

    return NULL;
}