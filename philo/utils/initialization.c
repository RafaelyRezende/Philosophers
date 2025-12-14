#include "philo.h"

int	initialize_locks_and_forks(t_table *table, t_philo *philos)
{
	int			i;

	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		if (pthread_create(&philos[i].thread_id , NULL, routine, (void *) table))
			return (2);
		i++;
	}
	table->start_time = get_time_ms();
	table->sim_running = 1;
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(philos[i].thread_id , NULL))
			return (2);
		i++;
	}
	return (0);
}
