/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:06:13 by rluis-ya          #+#    #+#             */
/*   Updated: 2026/01/03 19:06:21 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	error_number_of_args(void);
static int	is_valid_number(char *str);

void	initialize_wrapper(int argc, char **argv, t_table *table)
{
	int	status;

	status = initialize_table_params(argc, argv, table);
	if (status)
		exit (status);
}

int	initialize_table_params(int argc, char **argv, t_table *table)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error_number_of_args(), 1);
	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
			return (printf("Error: arguments must be positive numbers.\n"), 1);
		i++;
	}
	table->philo_count = ft_atol_positive(argv[1]);
	table->time_to_die = ft_atol_positive(argv[2]);
	table->time_to_eat = ft_atol_positive(argv[3]);
	table->time_to_sleep = ft_atol_positive(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atol_positive(argv[5]);
	else
		table->must_eat_count = -1;
	if (table->philo_count < 1 || table->philo_count > 200)
		return (printf("Error: invalid simulation value.\n"), 1);
	return (initialize_table_semaphores(table));
}

static
void	error_number_of_args(void)
{
	printf("Error: wrong number of arguments.\n");
	printf("\n\tUSAGE:\n");
	printf("\t\t[Number of philosophers]\n");
	printf("\t\t[Time to die]\n");
	printf("\t\t[Time to eat]\n");
	printf("\t\t[Time to sleep]\n");
	printf("\t\t(Optional) [Number of times each philosopher must eat]\n");
}

static
int	is_valid_number(char *str)
{
	if (*str == '\0')
		return (1);
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}
