#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer(char *file);
void close_files(int file1, int file2);

/**
 * allocate_buffer - Allocates memory for a buffer.
 * @file: The name of the file the buffer is for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *allocate_buffer(char *file)
{
char *buffer;
buffer = malloc(sizeof(char) * 1024);
if (buffer == NULL)
{
dprintf(STDERR_FILENO,
"Error: Cannot allocate memory for %s\n", file);
exit(99);
}
return (buffer);
}

/**
 * close_files - Closes file descriptors.
 * @file1: The first file descriptor to be closed.
 * @file2: The second file descriptor to be closed.
 */
void close_files(int file1, int file2)
{
int result;
result = close(file1);
if (result == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot close file descriptor %d\n", file1);
exit(100);
}
result = close(file2);
if (result == -1)
{
dprintf(STDERR_FILENO, "Error: Unable to close file descriptor %d\n", file2);
exit(100);
}
}

/**
 * main - Copies the contents of one file to another.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 * If the source file does not exist or cannot be read - exit code 98.
 * If the destination file cannot be created or written to - exit code 99.
 * If either file cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
int source, destination, read_result, write_result;
char *buffer;
if (argc != 3)
{
dprintf(STDERR_FILENO, "Usage: copy source_file destination_file\n");
exit(97);
}
buffer = allocate_buffer(argv[2]);
source = open(argv[1], O_RDONLY);
read_result = read(source, buffer, 1024);
destination = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
do {
if (source == -1 || read_result == -1)
{
dprintf(STDERR_FILENO,
"Error: Cannot read from file %s\n", argv[1]);
free(buffer);
exit(98);
}
write_result = write(destination, buffer, read_result);
if (destination == -1 || write_result == -1)
{
dprintf(STDERR_FILENO,
"Error: Cannot write to file %s\n", argv[2]);
free(buffer);
exit(99);
}
read_result = read(source, buffer, 1024);
destination = open(argv[2], O_WRONLY | O_APPEND);
} while (read_result > 0);
free(buffer);
close_files(source, destination);
return (0);
}
