#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(uint64_t time_in_ms, t_table *table)
{
	(void)table;
	uint64_t	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
		usleep(500);
}
