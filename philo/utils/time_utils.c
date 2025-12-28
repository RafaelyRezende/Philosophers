#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) <= -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms, t_table *table)
{
	long long	start_time;

	(void)table;
	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
		usleep(100);
}
