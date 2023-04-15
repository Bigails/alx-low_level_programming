#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "main.h"

/**
 * read_textfile - it Reads a text file and prints it to the POSIX standard output
 * @filename: The name of the file to be read
 * @letters: The number of letters to read and print
 *
 * Return: The actual number of letters read and printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fl, rc, wc;
	char *buff;

	if (filename == NULL) /*check if the file is present*/
	return (0);

	fl = open(filename, O_RDONLY); /*open the file*/
	if (fl == -1)
	return (0);

	buff = malloc(sizeof(char) * letters);	
	if (buff == NULL)
	{
	close(fl);
	return (0);
	}

	rc = read(fl, buff, letters);
	if (rc == -1)
	{
	free(buff);
	close(fl);
	return (0);
	}

	wc = write(STDOUT_FILENO, buff, rc);
	if (wc == -1 || wc != rc)
	{
	free(buff);
	close(fl);
	return (0);
    }

	free(buff);
	close(fl); /*close file*/
	return (rc);
}
