#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer(char *filename);
void close_file(int file_descriptor);

/**
 * allocate_buffer - Allocates 1024 bytes for a buffer.
 * @filename: The name of the file the buffer is being allocated for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *allocate_buffer(char *filename)
{
char *buffer;
buffer = malloc(sizeof(char) * 1024);
if (buffer == NULL)
{
dprintf(STDERR_FILENO,
"Error: Cannot allocate buffer for %s\n", filename);
exit(99);
}
return (buffer);
}

/**
 * close_file - Closes file descriptors.
 * @fd: The file descriptor to be closed.
 */
void close_file(int fd)
{
int result;
result = close(fd);
if (result == -1)
{
dprintf(STDERR_FILENO, "Error: Unable to close file descriptor %d\n", fd);
exit(100);
}
}

/**
 * main - Copies the contents of one file to another.
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: Exits with error code 97 if the argument count is incorrect.
 * Exits with error code 98 if file_from does not exist or cannot be read.
 * Exits with error code 99 if file_to cannot be created or written to.
 * Exits with error code 100 if file_to or file_from cannot be closed.
 */
int main(int argc, char *argv[])
{
int source_file, destination_file, read_result, write_result;
char *buffer;
if (argc != 3)
{
dprintf(STDERR_FILENO, "Usage: cp source_file destination_file\n");
exit(97);
}
buffer = allocate_buffer(argv[2]);
source_file = open(argv[1], O_RDONLY);
read_result = read(source_file, buffer, 1024);
destination_file = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
do {
if (source_file == -1 || read_result == -1)
{
dprintf(STDERR_FILENO,
"Error: Cannot read from file %s\n", argv[1]);
free(buffer);
exit(98);
}
 write_result = write(destination_file, buffer, read_result);
if (destination_file == -1 || write_result == -1)
{
dprintf(STDERR_FILENO,
"Error: Cannot write to %s\n", argv[2]);
free(buffer);
exit(99);
}
read_result = read(source_file, buffer, 1024);
destination_file = open(argv[2], O_WRONLY | O_APPEND);
} while (read_result > 0);
free(buffer);
close_file(source_file);
close_file(destination_file);
return (0);
}
