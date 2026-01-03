/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:05:03 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/01/03 19:05:05 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	reaper(t_table *table);
static void	kill_all(t_table *table);
static void	cleanup(t_table *table);

int	main(int argc, char **argv)
{
	t_table			table;
	static t_philo	philos[MAX_PHILO];
	static pid_t	pids[MAX_PHILO];

	initialize_wrapper(argc, argv, &table);
	initialize_philos(&table, philos, pids);
	start_simulation(&table);
	reaper(&table);
	cleanup(&table);
	return (0);
}

static
void	kill_all(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		kill(table->pids[i], SIGKILL);
		i++;
	}
}

static
void	reaper(t_table *table)
{
	int		i;
	int		status;
	int		exit_code;
	pid_t	pid;

	i = 0;
	while (i < table->philo_count)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status))
		{
			exit_code = WIFEXITED(status);
			if (exit_code == 1)
			{
				kill_all(table);
				return ;
			}
		}
		i++;
	}
}

static
void	cleanup(t_table *table)
{
	sem_close(table->sem_forks);
	sem_close(table->sem_write);
	sem_close(table->sem_q);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_q");
}
