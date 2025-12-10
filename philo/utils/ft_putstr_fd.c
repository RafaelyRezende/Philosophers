#include "philo.h"

ssize_t	ft_putstr_fd(int fd, char *buff)
{
	size_t	length;
	char	*start;

	if (!buff || fd < 0)
		return (-1);
	start = buff;
	length = 0;
	while (*buff)
	{
		length++;
		buff++;
	}
	write(fd, start, length);
	return (0);
}
