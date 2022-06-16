#include "minish.h"

int builtin_pid()
{
  printf("ID del proceso: %d\n", getpid());
  return 0;
}