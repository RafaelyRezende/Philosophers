#include "philo.h"

static int	initialize_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
	{
		pthead_mutex_destroy(&table->write_lock);
		return (1);
	}
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->sim_lock);
			pthread_mutex_destroy(&table->write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize_simulation(t_table *table, t_philo *philos)
{
	int	i;

	table->sim_running = 1;
	if (initialize_mutexes(table))
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].table = table;
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % table->philo_count];
		if (pthread_mutex_init(&table->philos[i].meal_lock, NULL) != 0)
		{
			cleanup_table(table, "Error: Mutex init failed\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	cleanup_table(t_table *table, char *msg, int exit_code)
{
	int	i;

	if (msg)
		ft_putstr_fd(2, msg);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_lock);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_lock);
		i++;
	}
	if (exit_code != 0)
		exit(exit_code);
}
