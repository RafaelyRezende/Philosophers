#include "philo.h"

int	main(const int argc, char **argv)
{
	static t_table			table;
	static t_philo			philos[MAX_PHILO];
	static pthread_mutex_t	forks[MAX_PHILO];

	table.philos = philos;
	table.forks = forks;
	if (parse_philos(argc, argv, &table) != 0)
		return (1);
	if (initialize_simulation(&table) != 0)
		return (1);
	
	// TODO: create_threads(&table);
	// TODO: monitor(&table);
	
	cleanup_table(&table, NULL, 0);
	return (0);
}

void	*routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	ft_usleep(1000, table);
	return (NULL);
}
