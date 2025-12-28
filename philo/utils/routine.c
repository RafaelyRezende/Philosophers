/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:31:30 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:32:07 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->sim_lock);
	if (philo->table->sim_running)
	{
		pthread_mutex_lock(&philo->table->write_lock);
		printf("%lld\tPhilo %d %s\n", \
get_time_ms() - philo->table->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->table->write_lock);
	}
	pthread_mutex_unlock(&philo->table->sim_lock);
}

static void	handle_one(t_table *table, pthread_mutex_t *ff)
{
	if (table->philo_count == 1)
	{
		ft_usleep(table->time_to_die * 2, table);
		pthread_mutex_unlock(ff);
	}
}

static void	assign_forks(t_philo *philo,
		pthread_mutex_t **ff, pthread_mutex_t **sf)
{
	if (philo->id % 2 == 0)
	{
		*ff = philo->right_fork;
		*sf = philo->left_fork;
	}
	else
	{
		*ff = philo->left_fork;
		*sf = philo->right_fork;
	}
}

static void	routine_eat(t_philo *philo)
{
	pthread_mutex_t	*ff;
	pthread_mutex_t	*sf;

	assign_forks(philo, &ff, &sf);
	pthread_mutex_lock(ff);
	print_status(philo, "has taken a fork.");
	handle_one(philo->table, ff);
	pthread_mutex_lock(sf);
	print_status(philo, "has taken a fork.");
	pthread_mutex_lock(&philo->meal_lock);
	print_status(philo, "is eating.");
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(ff);
	pthread_mutex_unlock(sf);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->table);
	while (1)
	{
		pthread_mutex_lock(&philo->table->sim_lock);
		if (!philo->table->sim_running)
		{
			pthread_mutex_unlock(&philo->table->sim_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->sim_lock);
		routine_eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->table->time_to_sleep, philo->table);
		print_status(philo, "is thinking");
		if (philo->table->philo_count % 2 != 0)
			ft_usleep(60, philo->table);
	}
	return (NULL);
}
