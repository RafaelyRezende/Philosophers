#include "philo.h"

static void	end_simulation(t_table *table);

int	run_simulation(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_lock(&table->philos[i].meal_lock);
		table->philos[i].last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[i].meal_lock);
		if (pthread_create(&table->philos[i].thread_id, NULL, \
routine, (void *)&table->philos[i]) != 0)
		{
			pthread_mutex_lock(&table->sim_lock);
			table->sim_running = 0;
			pthread_mutex_unlock(&table->sim_lock);
			while (--i >= 0)
				pthread_join(table->philos[i].thread_id, NULL);
			return (1);
		}
		i++;
	}
	monitor_simulation(table);
	end_simulation(table);
	return (0);
}

static void	end_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}
