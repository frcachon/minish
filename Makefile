# La variable CC indica el ejecutable para el compilador C (usualmente son gcc o clang)
#CC=gcc
# La variable CFLAGS indica las banderas para el compilador C
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb
# La variable LDLIBS indica las banderas para la parte del "loader", usualmente librerías "-lxxxx"
#LDLIBS=

# Este sería el ejecutable, sus dependencias son los .o
minish: minish.o builtin.o linea2argv.o ejecutar.o externo.o builtin_cd.o builtin_dir.o builtin_help.o builtin_exit.o builtin_status.o builtin_setenv.o builtin_unsetenv.o builtin_getenv.o builtin_pid.o builtin_history.o builtin_gid.o builtin_uid.o

# Acá van los .o, make sabe que cada .o depende del .c correspondiente, acá se agrega la dependencia al .h
minish.o: minish.h
builtin.o: builtin.h