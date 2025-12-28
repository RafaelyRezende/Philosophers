#include "philo.h"

static int	check_must_eat_count(t_table *table, int *n_eaten)
{
	if (table->must_eat_count == -1)
		return (1);
	if (*n_eaten == tbale->philo_count)
	{
		pthread_mutex_lock(table->sim_lock);
		table->sim_running = 0;
		pthread_mutex_unlock(table->sim_lock);
		return (1);
	}
	return (0);
}

static void	handle_death(t_table *table, int id)
{
	pthread_mutex_lock(table->sim_lock);
	table->sim_running = 0;
	pthread_mutex_unlock(table->sim_lock);
	
	pthread_mutex_lock(table->write_lock);
	printf("%lld\tPhilo %i died.", get_time_ms() - table->start_time, id);
	pthread_mutex_unlock(table->write_lock);
}

void	monitor_simulation(t_table *table)
{
	int			i;
	int			n_eaten;
	long long	now;

	while (1)
	{
		i = 0;
		n_eaten = 0;
		while (i < table->philo_count)
		{
			pthread_mutex_lock(table->philo[i]->meal_lock);
			now = get_time_ms();
			if (now - table->start_time >= table->time_to_die)
			{
				pthread_mutex_unlock(table->philo[i]->meal_lock);
				handle_death(table, table->philo[i].id);
				return ;
			}
			if (table->must_eat_count != -1 &&\
					table->philo[i].meals_eaten >= table->must_eat_count)
				n_eaten++;
			i++;
		}
		if (check_must_eat_count(table, &n_eaten))
			return ;
		ft_usleep(500);
	}
}
