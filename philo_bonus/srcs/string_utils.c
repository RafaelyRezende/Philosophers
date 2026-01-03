/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:06:37 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/01/03 19:06:38 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static
void	ft_itoa(int n, char *buffer)
{
	if (n >= 0 && n <= 9)
	{
		*buffer = n + '0';
		*(buffer + 1) = '\0';
		return ;
	}
	ft_itoa(n / 10, buffer);
	while (*buffer)
		buffer++;
	*buffer = (n % 10) + '0';
	*(buffer + 1) = '\0';
}

void	instanciate_name(int id, char *name)
{
	name[0] = '/';
	name[1] = 'p';
	name[2] = '_';
	ft_itoa(id, name + 3);
}

void	subroutine_eat(t_philo *philo)
{
	if (sem_wait(philo->sem_philo_meal) == -1)
		handle_exit("Error meal wait semaphore\n");
	philo->last_meal = get_time_ms();
	philo->meals_eaten++;
	if (sem_post(philo->sem_philo_meal) == -1)
		handle_exit("Error meal post semaphore\n");
	handle_print(philo, "is eating.");
	ft_usleep(philo->table->time_to_eat);
}

void	helper_routine(t_philo *philo)
{
	handle_print(philo, "is sleeping.");
	ft_usleep(philo->table->time_to_sleep);
	handle_print(philo, "is thinking.");
	usleep(500);
}
