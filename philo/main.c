#include "philo.h"

void	*routine(void *ptr)
{
	ft_putstr_fd(1, buf);
	usleep(3000000);
	ft_putstr_fd(1, "End routine.\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	void		**start_routine;

	start_routine = &routine("Start routine.\n");
	pthread_create(&t1, NULL, *start_routine, NULL);
	pthread_create(&t2, NULL, *start_routine, NULL);
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
