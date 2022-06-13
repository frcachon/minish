#include "builtin.h"

int builtin_status(int argc, char **argv) {
	if (argc == 1) {
		printf("%s: %d\n", argv[0],globalstatret);
    return 0;
	} else {
		error(EXIT_SUCCESS, 0, "No se admiten parametros.");
		return 1;
	}
}