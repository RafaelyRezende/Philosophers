#include "philo.h"

int	main(int argc, char **argv)
{
	static t_table			table;
	static t_philo			philos[200];
	static pthread_mutex_t	forks[200];

	table.philos = philos;
	table.forks = forks;
	parse_philos(argc, argv, &table);
	return (0);
}
