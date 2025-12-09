#include "philo.h"

void	opt_main(char **argv)
{
	ft_putstr_fd(stdin, argv[1]);
}

ssize_t	ft_putstr_fd(int fd, char *buff)
{
	size_t	lenght;
	char	*start;

	if (!buff)
		return (-1);
	start = buff;
	lenght = 0;
	while (*buff)
	{
		lenght++;
		buff++;
	}
	write(fd, start, length);
	return (0);
}
