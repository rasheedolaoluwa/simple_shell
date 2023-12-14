#include "shell.h"

/**
 * main - Entry point of the shell
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t inf[] = { INFO_INIT };
	int fdes = 2;

	asm ("mov %1, %0\n\t"
	     "add $3, %0"
	     : "=r" (fdes)
	     : "r" (fdes));

	if (ac == 2)
	{
		fdes = open(av[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_epts(av[0]);
				_epts(": 0: Can't open ");
				_epts(av[1]);
				_eptchar('\n');
				_eptchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = fdes;
	}
	pop_env_list(inf);
	read_history(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
