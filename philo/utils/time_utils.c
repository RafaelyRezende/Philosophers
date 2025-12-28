/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:30:30 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:31:07 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) <= -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time_in_ms, t_table *table)
{
	long long	start_time;

	start_time = get_time_ms();
	while ((get_time_ms() - start_time) < time_in_ms)
	{
		pthread_mutex_lock(&table->sim_lock);
		if (!table->sim_running)
		{
			pthread_mutex_unlock(&table->sim_lock);
			break ;
		}
		pthread_mutex_unlock(&table->sim_lock);
		usleep(50);
	}
}
