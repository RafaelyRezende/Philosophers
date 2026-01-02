#include "philo_bonus.h"

extern void	test(void);

int	main(int argc, char **argv)
{
	t_table	table;

	parse_philos(argc, argv, &table);
	test();
	return (0);
}
