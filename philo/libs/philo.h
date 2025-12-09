#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stddef.h>

typedef struct s_thread_data
{
	char			*str;
	pthread_mutex_t	*lock;
}	t_thread_data;

void	opt_main(char **argv);
void	standard_main(char **argv);
ssize_t	ft_putstr_fd(int fd, char *buff);

#endif
