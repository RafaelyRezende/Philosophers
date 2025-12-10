#include "philo.h"

static void	initialize_data(t_thread_data *data, int argc, char **argv);
static int	error_number_of_args(void);

void	*routine(void *data)
{
	long	*ptr;

	ptr = (long *) data;
	printf("%ld\n", *ptr);
	usleep(1000000);
	ft_putstr_fd(1, "End routine 1.\n");
	return (NULL);
}

void	*routine2(void *data)
{
	long	*ptr;

	ptr = (long *) data;
	printf("%ld\n", *ptr);
	usleep(2000000);
	ft_putstr_fd(1, "End routine 2.\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_thread_data	data;
	pthread_t		t1;
	pthread_t		t2;

	if (argc < 5 || argc > 6)
		return (error_number_of_args());
	initialize_data(&data, argc, argv);
	pthread_create(&t1, NULL, routine, (void *) &data.number_of_philos);
	pthread_create(&t2, NULL, routine2, (void *) &data.time_to_die);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}

static
void	initialize_data(t_thread_data *data, int argc, char **argv)
{
	if (argc == 5 )
		data->number_of_cycles = -1;
	else
		data->number_of_cycles = ft_atoi(argv[argc - 1]);

	data->number_of_philos = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->time_to_die = ft_atoi(argv[4]);
}

static
int	error_number_of_args(void)
{
	ft_putstr_fd(2, "Wrong number of arguments.\n");
	ft_putstr_fd(2, "\n\tUSAGE:\n");
	ft_putstr_fd(2, "\t\t[Number of philosophers]\n");
	ft_putstr_fd(2, "\t\t[Time to die]\n");
	ft_putstr_fd(2, "\t\t[Time to eat]\n");
	ft_putstr_fd(2, "\t\t[Time to sleep]\n");
	ft_putstr_fd(2, "\t\t(Optional) [Number of times each philosopher must eat]\n");
	return (-1);
}
/*
int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 5)
		standard_main(argv);
	else
		opt_main(argv);
	return (0);
}
*/
