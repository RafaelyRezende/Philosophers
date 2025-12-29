/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:32:31 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:33:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_mutexes(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->sim_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->write_lock);
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

int	initialize_simulation(t_table *table)
{
	int	i;

	table->sim_running = 1;
	if (initialize_mutexes(table))
		return (1);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = \
&table->forks[(i + 1) % table->philo_count];
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
		printf("%s\n", msg);
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
