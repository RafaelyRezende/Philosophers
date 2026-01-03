#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table			table;
	static t_philo	philos[MAX_PHILO];
	static pid_t	pids[MAX_PHILO];

	initialize_wrapper(argc, argv, &table);
	initialize_philos(&table, philos, pids);
	start_simulation(&table);
	int	i = 0;
	while (i < table.philo_count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	return (0);
}
