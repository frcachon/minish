#include "minish.h"

void builtin_gid()
{
  printf("Group ID: %d\n", getgid());
}