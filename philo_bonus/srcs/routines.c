/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:07:29 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/01/03 19:11:21 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitor_routine(void *arg);
static void	launch_monitor(t_philo *philo, char *name);
static void	join_monitor(t_philo *philo);

void	routine(void *arg)
{
	t_philo	*philo;
	char	name[20];

	philo = (t_philo *) arg;
	launch_monitor(philo, name);
	while (1)
	{
		if (sem_wait(philo->table->sem_q) == -1)
			handle_exit("Error semaphore queue wait\n");
		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks wait 1\n");
		handle_print(philo, "has taken a fork.");
		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks wait 2\n");
		handle_print(philo, "has taken a fork.");
		subroutine_eat(philo);
		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks post 1\n");
		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks post 2\n");
		if (sem_post(philo->table->sem_q) == -1)
			handle_exit("Error semaphore queue post\n");
		helper_routine(philo);
	}
	join_monitor(philo);
}

static
void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	long long	time_since_meal;
	int			eaten_copy;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->sem_philo_meal);
		time_since_meal = get_time_ms() - philo->last_meal;
		eaten_copy = philo->meals_eaten;
		sem_post(philo->sem_philo_meal);
		if (time_since_meal >= philo->table->time_to_die)
		{
			sem_wait(philo->table->sem_write);
			printf("%lld %d died\n", \
get_time_ms() - philo->table->start_time, philo->id);
			exit(1);
		}
		if (philo->table->must_eat_count != -1 && \
eaten_copy >= philo->table->must_eat_count)
			exit(0);
		usleep(1000);
	}
	return (NULL);
}

static
void	launch_monitor(t_philo *philo, char *name)
{
	while (get_time_ms() < philo->table->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		ft_usleep(20);
	philo->sem_name = name;
	instanciate_name(philo->id, philo->sem_name);
	sem_unlink(philo->sem_name);
	philo->sem_philo_meal = sem_open(philo->sem_name, O_CREAT, 0644, 1);
	if (philo->sem_philo_meal == SEM_FAILED)
		exit(1);
	if (pthread_create(&philo->thread, NULL, \
monitor_routine, philo) != 0)
		handle_exit("Error thread create\n");
}

static
void	join_monitor(t_philo *philo)
{
	if (pthread_join(philo->thread, NULL) != 0)
		handle_exit("Error thread join\n");
	sem_close(philo->sem_philo_meal);
	sem_unlink(philo->sem_name);
}

void	handle_print(t_philo *philo, const char *str)
{
	if (sem_wait(philo->table->sem_write) == -1)
		handle_exit("Error semaphore write wait\n");
	printf("%lld\t#%d   %s\n", get_time_ms() - philo->table->start_time, \
philo->id, str);
	if (sem_post(philo->table->sem_write) == -1)
		handle_exit("Error semaphore write post\n");
}
