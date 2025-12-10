#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

typedef struct s_table t_table;
typedef struct s_philo
{
	int	id;
	size_t	meals_eaten;
	size_t	last_meal;
	pthread_t	thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
    long            philo_count;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    long            must_eat_count;
    long            start_time;
    bool            sim_running;
    pthread_mutex_t write_lock;
    pthread_mutex_t sim_lock;
    pthread_mutex_t *forks;
    t_philo         *philos;
} t_table;

long	ft_atol(const char *nptr);
ssize_t	parse_philos(int argc, char **argv, t_params *params);
ssize_t	ft_putstr_fd(int fd, char *buff);
ssize_t	init_env();

#endif
