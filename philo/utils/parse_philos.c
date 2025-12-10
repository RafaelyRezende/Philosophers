#include "philo.h"

static ssize_t	error_number_of_args(void);
static bool		is_valid_number(char *str);

ssize_t	parse_philos(int argc, char **argv, t_params *params)
{
	static int	num[5];
	long		tmp;

	if (argc < 5 || argc > 6)
		return (error_number_of_args());
	while (--argc > 0)
	{
		tmp = ft_atol(argv[argc]);
		if (tmp == LONG_MAX)
			return (ft_putstr_fd(1, "Invalid number.\n"));
		num[argc - 1] = (int) tmp;
		if (argc == 1 && (num[argc - 1] > 200 || num[argc - 1] < 1))
			return (ft_putstr_fd(1, "Invalid number of philosophers.\n"));
	}
	params->number_of_philos = (size_t) num[0];
	params->time_to_eat = (size_t) num[1];
	params->time_to_sleep = (size_t) num[2];
	params->time_to_die = (size_t) num[3];
	params->opt = (size_t) num[4];
	return (0);
}

static ssize_t	error_number_of_args(void)
{
	ft_putstr_fd(1, "Wrong number of arguments.\n");
	ft_putstr_fd(1, "\n\tUSAGE:\n");
	ft_putstr_fd(1, "\t\t[Number of philosophers]\n");
	ft_putstr_fd(1, "\t\t[Time to die]\n");
	ft_putstr_fd(1, "\t\t[Time to eat]\n");
	ft_putstr_fd(1, "\t\t[Time to sleep]\n");
	ft_putstr_fd(1, "\t\t(Optional) [Number of times each philosopher must eat]\n");
	return (-1);
}
