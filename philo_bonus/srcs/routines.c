#include "philo_bonus.h"

static void	*monitor_routine(void *arg);
static void	launch_monitor(t_philo *philo, char *name);
static void	join_monitor(t_philo *philo);

void	routine(void *arg)
{
	t_philo	*philo;
	char	name[20];

	philo = (t_philo *) arg;
	if (philo->id % 2 != 0)
		ft_usleep(15);
	launch_monitor(philo, name);
	while (1)
	{
		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks wait 1\n");
		handle_print(philo, "has taken a fork.");
		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks wait 2\n");
		handle_print(philo, "has taken a fork.");
		subroutine_eat(philo);
		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks post 1\n");
		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit("Error semaphore forks post 2\n");
		handle_print(philo, "is sleeping.");
		ft_usleep(philo->table->time_to_sleep);
		handle_print(philo, "is thinking.");
	}
	join_monitor(philo);
}

static
void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	long long	delta_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		if (sem_wait(philo->sem_philo_meal) == -1)
			handle_exit("Error read meal semaphore wait\n");
		delta_meal = get_time_ms() - philo->last_meal;
		if (sem_post(philo->sem_philo_meal) == -1)
			handle_exit("Error read meal semaphore post\n");
		if (delta_meal >= philo->table->time_to_die)
		{
			if (sem_wait(philo->table->sem_write) == -1)
				handle_exit("Error write semaphore wait on monitor\n");
			printf("%lld\t#%d\t%s\n", \
get_time_ms() - philo->table->start_time, philo->id, "died");
			exit(1);
		}
		if (philo->table->must_eat_count != -1 && \
philo->meals_eaten == philo->table->must_eat_count)
			exit(0);
		ft_usleep(1);
	}
	return (NULL);
}

static
void	launch_monitor(t_philo *philo, char *name)
{
	philo->sem_name = name;
	instanciate_name(philo->id, philo->sem_name);
	sem_unlink(philo->sem_name);
	philo->sem_philo_meal = sem_open(philo->sem_name, O_CREAT, 0644, 1);
	if (philo->sem_philo_meal == SEM_FAILED)
		exit(1);
	if (pthread_create(&philo->thread, NULL, \
monitor_routine, (void *)philo) == -1)
		handle_exit("Error thread create\n");
}

static
void	join_monitor(t_philo *philo)
{
	if (pthread_join(philo->thread, NULL) != 0)
		handle_exit("Error thread join\n");
}

void	handle_print(t_philo *philo, const char *str)
{
	if (sem_wait(philo->table->sem_write) == -1)
		handle_exit("Error semaphore write wait\n");
	printf("%lld\t#%d   %s\n", get_time_ms() - philo->table->start_time, \
philo->id, str);
	if (sem_post(philo->table->sem_write) == -1)
		handle_exit("Error semaphore write post\n");
}
