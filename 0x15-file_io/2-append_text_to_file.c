#include "main.h"

/**
 * append_text_to_file - Appends text at the end of a file.
 *
 * @filename: Name of the file.
 * @text_content: The text to add to the end of the file.
 *
 * Return: If successful - 1.
 *         If filename is NULL or the function fails - -1.
 */
int append_text_to_file(const char *filename, char *text_content)
{
int fd, write_count, text_len = 0;
if (!filename)
return (-1);
if (text_content)
{
while (text_content[text_len])
text_len++;
}
fd = open(filename, O_WRONLY | O_APPEND);
if (fd == -1)
return (-1);
write_count = write(fd, text_content, text_len);
if (write_count == -1 || write_count != text_len)
{
close(fd);
return (-1);
}
close(fd);
return (1);
}
