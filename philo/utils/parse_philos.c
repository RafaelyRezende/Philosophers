/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rluis-ya <rluis-ya@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 20:32:10 by rluis-ya          #+#    #+#             */
/*   Updated: 2025/12/28 20:32:29 by rluis-ya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	error_number_of_args(void);
static int	is_valid_number(char *str);

int	parse_philos(int argc, char **argv, t_table *table)
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
	if (table->philo_count < 1 || table->philo_count > 200 || \
table->philo_count <= 0 || \
table->time_to_die <= 0 || \
table->time_to_eat <= 0 || \
table->time_to_sleep <= 0)
		return (printf("Error: invalid simulation value.\n"), 1);
	return (0);
}

static void	error_number_of_args(void)
{
	printf("Error: wrong number of arguments.\n");
	printf("\n\tUSAGE:\n");
	printf("\t\t[Number of philosophers]\n");
	printf("\t\t[Time to die]\n");
	printf("\t\t[Time to eat]\n");
	printf("\t\t[Time to sleep]\n");
	printf("\t\t(Optional) [Number of times each philosopher must eat]\n");
}

static int	is_valid_number(char *str)
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
