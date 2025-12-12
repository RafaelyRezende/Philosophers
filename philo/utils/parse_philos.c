#include "philo.h"

static void		error_number_of_args(void);
static uint8_t	is_valid_number(char *str);
static uint8_t	init_table(t_table *table);

uint8_t	parse_philos(int argc, char **argv, t_table *table)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (error_number_of_args(), 1);
	i = 1;
	while (i < argc)
	{
		if (is_valid_number(argv[i]))
			return (ft_putstr_fd(2, \
"Error: arguments must be positive numbers.\n"), 1);
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
		return (ft_putstr_fd(2, "Error: invalid simulation value.\n"), 1);
	if (init_table(table))
		return (ft_putstr_fd(2, "Error: could not initialize table.\n"), 1);
	return (0);
}

static void	error_number_of_args(void)
{
	ft_putstr_fd(2, "Error: wrong number of arguments.\n");
	ft_putstr_fd(2, "\n\tUSAGE:\n");
	ft_putstr_fd(2, "\t\t[Number of philosophers]\n");
	ft_putstr_fd(2, "\t\t[Time to die]\n");
	ft_putstr_fd(2, "\t\t[Time to eat]\n");
	ft_putstr_fd(2, "\t\t[Time to sleep]\n");
	ft_putstr_fd(2, \
"\t\t(Optional) [Number of times each philosopher must eat]\n");
}

static uint8_t	is_valid_number(char *str)
{
	if (*str == '\0')
		return (1);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

static uint8_t	init_table(t_table *table)
{
	if (pthread_mutex_init(&table->write_lock, NULL) == -1)
		return (free(table->philos), free(table->forks), 1);
	if (pthread_mutex_init(&table->sim_lock, NULL) == -1)
		return (free(table->philos), free(table->forks), 1);
	return (0);
}
