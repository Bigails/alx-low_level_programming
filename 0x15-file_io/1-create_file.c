#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
* create_file - creates a file with specified permissions
* and writes to it
* @filename: name of the file to create
* @text_content: NULL-terminated string to write to the file
*
* Return: 1 on success, -1 on failure
*/
int create_file(const char *filename, char *text_content)
{
	int fl, bytes_written, text_length = 0, mode = S_IRUSR | S_IWUSR;

	if (filename == NULL)
	return (-1);

	fl = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
	if (fl == -1)
	return (-1);

	if (text_content != NULL)
	{
	while (text_content[text_length] != '\0')
		text_length++;
	bytes_written = write(fl, text_content, text_length);
	if (bytes_written == -1)
	{
		close(fl);
		return (-1);
	}
	}

	close(fl);
	return (1);
}
