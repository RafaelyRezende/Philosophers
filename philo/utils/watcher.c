/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:27:30 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:30:25 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_must_eat_count(t_table *table, int *n_eaten)
{
	if (table->must_eat_count == -1)
		return (0);
	if (*n_eaten == table->philo_count)
	{
		pthread_mutex_lock(&table->sim_lock);
		table->sim_running = 0;
		pthread_mutex_unlock(&table->sim_lock);
		return (1);
	}
	return (0);
}

static void	handle_death(t_table *table, int id)
{
	pthread_mutex_lock(&table->sim_lock);
	table->sim_running = 0;
	pthread_mutex_unlock(&table->sim_lock);
	pthread_mutex_lock(&table->write_lock);
	printf("%lld\tPhilo %i died.\n", get_time_ms() - table->start_time, id);
	pthread_mutex_unlock(&table->write_lock);
}

static int	check_death(t_table *table, t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->meal_lock);
	now = get_time_ms();
	if ((now - philo->last_meal) >= table->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

void	monitor_simulation(t_table *table)
{
	int	i;
	int	n_eaten;

	while (1)
	{
		i = 0;
		n_eaten = 0;
		while (i < table->philo_count)
		{
			if (check_death(table, &table->philos[i]))
			{
				handle_death(table, table->philos[i].id);
				return ;
			}
			pthread_mutex_lock(&table->philos[i].meal_lock);
			if (table->must_eat_count != -1 && \
table->philos[i].meals_eaten >= table->must_eat_count)
				n_eaten++;
			pthread_mutex_unlock(&table->philos[i].meal_lock);
			i++;
		}
		if (check_must_eat_count(table, &n_eaten))
			return ;
		ft_usleep(1, table);
	}
}
