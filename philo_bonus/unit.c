#include "philo_bonus.h"

//#define S_NAME "/semsem"

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

int main(void)
{
	t_env		env;
	pid_t		pid[MAX_PHILO];

	initialize_environment(&env);
	sem_unlink(name);
	t = sem_open(name, O_CREAT, 0644, 1);
	if (t == SEM_FAILED)
		return (1);
	process_routine(pid);
	sem_close(t);
	sem_unlink(name);
	printf("[MAIN] Cleanup finished.\n");
	return (0);
}

void	child_routine(sem_t *sem)
{
	int	i;

	i = 5;
	printf("[Child] Attempting to wait on semaphore...\n");
	sem_wait(sem);
	printf("[Child] Semaphore locked. Sleeping for %d second...\n", i);
	sleep(i);
	printf("[Child] Waking up and posting semaphore.\n");
	sem_post(sem);
	printf("[Child] Exiting with status 42.\n");
	exit(42);
}

void	parent_routine(pid_t *pid)
{
	int	status;
	int	exit_code;

	printf("[Parent] Waiting for child (PID %d)...\n", *pid);
	waitpid(*pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		printf("[Parent] Child finished. Exit code: %d\n", exit_code);
	}
	else
		printf("[Parent] Child did not exit normally.\n");
}

void	process_routine(t_env *env)
{
	pid_t	at_pid;
	int		i;

	i = 0;
	while (i < MAX_PHILO)
	{
		at_pid = fork();
		if (at_pid == -1)
		{
			sem_close(env->smp);
			return ;
		}
		else
		{
		}
	}
	at_pid = fork();
	if (pid < 0)
	{
		printf("Error: fork failed");
		sem_close(t);
		sem_unlink(name);
		return (1);
	}
	if (pid == 0)
		child_routine(t);
	else
		parent_routine(&pid);
}

void	initialize_environment(t_env *env, pid_t *arr_pid)
{
	
}
