
#include "builtin.h"

int builtin_status(int argc, char **argv)
{
	if (argc > 0)
		printf("%s: %d\n", argv[0],globalstatret);
    return 0;
}