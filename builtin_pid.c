#include "minish.h"

void builtin_pid()
{
  printf("ID del proceso: %d\n", getpid());
}