#include "philo.h"

void	*routine(void *data)
{
	long	*ptr;

	ptr = (long *) data;
	printf("%ld\n", *ptr);
	usleep(1000000);
	ft_putstr_fd(1, "End routine.\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_thread_data	data;
	pthread_t		t1;
	pthread_t		t2;

	if (argc < 5 || argc > 6)
		return (-1);

	if (argc == 5)
		data.number_of_cycles = -1;
	else
		data.number_of_cycles = ft_atoi(argv[argc - 1]);

	data.number_of_philos = ft_atoi(argv[1]);
	data.time_to_eat = ft_atoi(argv[2]);
	data.time_to_sleep = ft_atoi(argv[3]);
	data.time_to_die = ft_atoi(argv[4]);

	pthread_create(&t1, NULL, routine, (void *) &data.number_of_philos);
	pthread_create(&t2, NULL, routine, (void *) &data.number_of_philos);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
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
