#include "main.h"

/**
 * set_bit - Is setting to 1 a bit at a given index 
 * @n: pointing to the number to be changed
 * @index: index of the bit to be set to 1
 *
 * Returing 1 in sueccess
 * Returning -1 in failure
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = ((1UL << index) | *n);
	return (1);
}
