#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	uint8_t			id;
	uint64_t		meals_eaten;
	uint64_t		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	uint32_t		philo_count;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		must_eat_count;
	uint64_t		start_time;
	uint8_t			sim_running;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

uint64_t	ft_atol_positive(const char *nptr);
uint8_t		parse_philos(int argc, char **argv, t_table *table);
void		ft_putstr_fd(int fd, char *buff);
void		cleanup_table(t_table *table);

#endif
