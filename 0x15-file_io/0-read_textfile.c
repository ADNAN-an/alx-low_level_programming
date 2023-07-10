#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads and prints the contents of a text file.
 *
 * @filename: Name of the text file.
 * @letters: Maximum number of letters to print.
 *
 * Return: If the function fails or filename is NULL - 0.
 *         Otherwise - the actual number of bytes read and printed.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
int fd;
char *buf;
ssize_t read_count, write_count;
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
if (fd == -1)
return (0);
buf = malloc(letters * sizeof(char));
if (!buf)
{
close(fd);
return (0);
}
read_count = read(fd, buf, letters);
if (read_count == -1)
{
free(buf);
close(fd);
return (0);
}
write_count = write(STDOUT_FILENO, buf, read_count);
if (write_count == -1 || write_count != read_count)
{
free(buf);
close(fd);
return (0);
}
free(buf);
close(fd);
return (write_count);
}
