#include "philo_bonus.h"

void	instantiate_name(int id, char *name)
{
	name[0] = '/';
	name[1] = 'p';
	name[2] = '_';
	ft_itoa(id, name + 3);
}

static
void	ft_itoa(int n, char *buffer)
{
	if (n >= 0 && n <= 9)
	{
		*buffer = n + '0';
		*(buffer + 1) = '\0';
		return ;
	}
	ft_itoa(n / 10, buffer);
	while (*buffer)
		buffer++;
	*buffer = (n % 10) + '0';
	*(buffer + 1) = '\0';
}
