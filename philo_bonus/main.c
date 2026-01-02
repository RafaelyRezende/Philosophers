#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table			table;
	static t_philo	philos[MAX_PHILO];
	static pid_t	pids[MAX_PHILO];

	initialize_wrapper(argc, argv, &table);
	initialize_philos(&table, philos, pids);
	return (0);
}
