#include "philo.h"

int	main(int argc, char **argv)
{
	static t_table	table;

	parse_philos(argc, argv, &table);
	cleanup_table(&table);
	return (0);
}
