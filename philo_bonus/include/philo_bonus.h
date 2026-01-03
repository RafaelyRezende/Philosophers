#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct s_table	t_table;

typedef enum e_sem_label
{
	SEM_ERR = 1,
	SEM_FORKS,
	SEM_WRITE,
	SEM_STOP
}	t_sem_label;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long long	last_meal;
	t_table		*table;
	pthread_t	thread;
	pid_t		pid;
}	t_philo;

typedef struct s_table
{
	long		philo_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		must_eat_count;
	long long	start_time;
	sem_t		*sem_forks; // Single semahpore for the forks (pool of forks)
	sem_t		*sem_write; // Equivalent to write_lock
	sem_t		*sem_meal; // Equivalent to meal_lock
	sem_t		*sem_stop; // Equivalent to sim_lock
	t_philo		*philos;
	pid_t		*pids;
}	t_table;

/* ----------------------- UTILS ------------------------ */

long		ft_atol_positive(const char *nptr);
int			ft_isspace(char s);

/* ----------------------- INITIALIZATION ------------------------ */

void		initialize_philos(t_table *table, t_philo *philos, pid_t *pids);
void		initialize_wrapper(int argc, char **argv, t_table *table);
int			initialize_table_params(int argc, char **argv, t_table *table);
int			initialize_table_semaphores(t_table *table);

/* ----------------------- ROUTINE ------------------------ */

void		start_simulation(t_table *table);
void		routine(void *arg);

/* ----------------------- TIME ------------------------ */

long long	get_time_ms(void);
void		ft_usleep(long time_in_ms, t_table *table);

/* ----------------------- ERRORS ------------------------ */

void		handle_exit(t_table *table, const char *str);

#endif
