#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#ifndef MAX_PHI
# deifne MAX_PHI 200
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

typedef struct	s_env
{
	sem_t		*sem;
	pid_t		*arr_pid;
	static char	name[8];
}	t_env;

void	parent_routine(pid_t *pid);
void	child_routine(sem_t *sem);
void	process_routine(pid_t *p);
void	initialize_environment(t_env *env, pid_t *arr_pid);

#endif
