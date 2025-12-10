#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_thread_mutex
{
	pthread_mutex_t	*lock;
}	t_thread_mutex;

typedef struct s_params
{
	size_t	number_of_philos;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_die;
	size_t	opt;
}	t_params;

long	ft_atol(const char *nptr);
ssize_t	parse_philos(int argc, char **argv, t_params *params);
ssize_t	ft_putstr_fd(int fd, char *buff);
ssize_t	init_env();

#endif
