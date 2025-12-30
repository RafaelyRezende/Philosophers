/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:33:28 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:33:29 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(const int argc, char **argv)
{
	static t_table			table;
	static t_philo			philos[MAX_PHILO];
	static pthread_mutex_t	forks[MAX_PHILO];

	if (parse_philos(argc, argv, &table) != 0)
		return (1);
	table.philos = philos;
	table.forks = forks;
	if (initialize_simulation(&table) != 0)
		return (1);
	if (run_simulation(&table) != 0)
		return (1);
	cleanup_table(&table, NULL);
	return (0);
}
