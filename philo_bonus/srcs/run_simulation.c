/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:07:16 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/01/03 19:07:17 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_simulation(t_table *table)
{
	int		i;

	table->start_time = get_time_ms() + 500;
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			handle_exit("Error create fork.\n");
		if (table->philos[i].pid == 0)
		{
			table->philos[i].last_meal = table->start_time;
			routine(&table->philos[i]);
			handle_exit(NULL);
		}
		table->pids[i] = table->philos[i].pid;
		i++;
	}
}

void	handle_exit(const char *str)
{
	if (str)
	{
		printf("%s", str);
		exit (1);
	}
	exit(0);
}
