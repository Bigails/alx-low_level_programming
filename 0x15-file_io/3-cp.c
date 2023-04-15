#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

/**
 * error_exit - print error message and exit with specified code
 * @code: exit code
 * @message: error message
 */
void error_exit(int code, const char *message)
{
	dprintf(STDERR_FILENO, "Error: %s\n", message);
	exit(code);
}

/**
 * cp - copy content from one file to another
 * @file_from: source file name
 * @file_to: destination file name
 */
void cp(const char *file_from, const char *file_to)
{
	int fd_from, fd_to, read_bytes, write_bytes;
	char buffer[BUFFER_SIZE];

	/* Open source file for reading */
	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
		error_exit(98, file_from);

	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd_to == -1)
		error_exit(99, file_to);

	/* Read from source file and write to destination file */
	while ((read_bytes = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		write_bytes = write(fd_to, buffer, read_bytes);
		if (write_bytes != read_bytes)
			error_exit(99, file_to);
	}

	if (read_bytes == -1)
		error_exit(98, file_from);

	/* Close file descriptors */
	if (close(fd_from) == -1)
		error_exit(100, "Can't close fd_from");
	if (close(fd_to) == -1)
		error_exit(100, "Can't close fd_to");
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: %s file_from file_to\n", argv[0]);
		exit(97);
	}

	cp(argv[1], argv[2]);

	return 0;
}

