#include "minish.h"

int builtin_history(int argc, char **argv){
  if (argc > 2){
    errno = E2BIG;
    perror("history");
    return errno;
  }
  else{
    int lineasDefecto = 10; 
    char *home;
    char minish_history_dir[MAXCWD];
    char *lineptr[MAXLINE];
    FILE *f;
    if ((home = getenv(HOME)) == NULL){
      perror("history");
      return errno;
    }
    snprintf(minish_history_dir, MAXCWD, "%s/%s", home, HISTORY_FILE);
    if ((f = fopen(minish_history_dir, "r")) == NULL){
      return errno;
    }
    if (argc > 1){
      lineasDefecto = atoi(argv[1]) - 1;
    }
    char line[MAXLINE];
    int nlines = 0;
    char *p;
    while (fgets(line, MAXLINE, f) != NULL){
      p = malloc(strlen(line));
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
    nlines--;
    while (nlines >= 0 && lineasDefecto >= 0){
      printf("%s", lineptr[nlines--]);
      lineasDefecto--;
    }
    if (fclose(f) == EOF){
      perror("history");
      return errno;
    }
  }
  return 0;
}