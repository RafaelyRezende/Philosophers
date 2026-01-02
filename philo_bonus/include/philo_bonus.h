#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal;
	pid_t		pid;
}	t_philo;

typedef struct s_table
{
	long	philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat_count;
	sem_t	*semaphores; // Array of semahpores
	sem_t	*sem_write; // Equivalent to write_lock
	sem_t	*sem_stop; // Equivalent to sim_lock
	t_philo	*philos;
	pid_t	*ppids;
}	t_table;

#endif
