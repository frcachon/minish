#include "minish.h"

int builtin_uid(){
    struct passwd *pwd;
    pwd = getpwuid(geteuid());
    printf("uid=%d(%s)",pwd->pw_uid,pwd->pw_name);
    return 0;
}