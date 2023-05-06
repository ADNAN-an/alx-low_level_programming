#include "main.h"

/**
 * get_endianness - will check if the machine is big or little endian
 * returning 1 for little and 0 for big
 */
int get_endianness(void)
{
	unsigned int i = 1;
	char *c = (char *) &i;

	return (*c);
}
i
