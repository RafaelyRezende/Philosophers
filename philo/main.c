#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (argc == 5)
		standard_main(argv);
	opt_main(argv);
	return (0);
}
