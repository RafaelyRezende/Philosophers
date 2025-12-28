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
	cleanup_table(&table, NULL, 0);
	return (0);
}
