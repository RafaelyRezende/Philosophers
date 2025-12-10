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

typedef struct s_thread_data
{
	ssize_t	number_of_philos;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	time_to_die;
	ssize_t	number_of_cycles;
	//pthread_mutex_t	*lock;
}	t_thread_data;

void	opt_main(char **argv);
void	standard_main(char **argv);
ssize_t	ft_putstr_fd(int fd, char *buff);
int		ft_atoi(const char *nptr);

#endif
