#include "./libs/philo.h"

int	main(const int argc, char **argv)
{
	static t_table			table;
	static t_philo			philos[MAX_PHILO];
	static pthread_mutex_t	forks[MAX_PHILO];

	table.philos = philos;
	table.forks = forks;
	parse_philos(argc, argv, &table);
	initialize_lock_and_forks(&table, &philos);
	return (0);
}
