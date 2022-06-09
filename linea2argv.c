#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define MAXLINE 1024
#define MAXWORDS 256
 
int linea2argv (char *linea, int argc, char **argv) {
    int words_qty = 0;

    int length = strlen(linea);

    char temp_word[MAXLINE];
    int letters_in_temp_word = -1;
    bool separacion = false;

    int separaciones = MAXWORDS - 1; // si me quedo sin separaciones, es porque ya tengo 256 palabras, entonces corto
    int i = 0;


    if(!isalnum(linea[0])){
        return words_qty;
    }

    for (; i < length; i++) {

        if (separaciones == 0) {
            printf("Maximo de palabras alcanzado. Se conservan las primeras 256 palabras.");
            break;
        }

        if (isalnum(linea[i])) {
                separacion = false;
                letters_in_temp_word++;
            temp_word[letters_in_temp_word] = linea[i];

        } else if (!separacion) {

                temp_word[i] = '\0';                           
                // termino la palabra entonces la guardo en argv y separaciones-- y words_qty++
                char* new_word = strdup(temp_word);
                argv[words_qty] = new_word;
                separaciones--;
                // if separaciones == -1
                words_qty++;
                memset(temp_word, 0, letters_in_temp_word);
                separacion = true;
                letters_in_temp_word = -1;
        }
    }
        
    argv[words_qty] = NULL;

    //for (int k = 0; k < 3; k++) {
    //        printf("%s\n", argv[k]);
    //}

    return words_qty;
}