#include "main.h"

/**
 * clear_bit - Is setting the value of a given bit to 0
 * @n: pointing to the number to be changed
 * @index: index of the bit to clear
 *
 * Returning 1 in success
 * Returning -1 in failure
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = (~(1UL << index) & *n);
	return (1);
}
