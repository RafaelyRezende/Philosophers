#include "philo_bonus.h"

static void	handle_print(t_philo *philo, const char *str);

void routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit(philo->table, "Error semaphore forks wait 1\n");
		handle_print(philo, "has taken a fork.");

		if (sem_wait(philo->table->sem_forks) == -1)
			handle_exit(philo->table, "Error semaphore forks wait 2\n");
		handle_print(philo, "has taken a fork.");

		handle_print(philo, "is eating.");
		philo->last_meal = get_time_ms();
		ft_usleep(philo->table->time_to_eat, philo->table);
		philo->meals_eaten++;

		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit(philo->table, "Error semaphore forks post 1\n");
		if (sem_post(philo->table->sem_forks) == -1)
			handle_exit(philo->table, "Error semaphore forks post 2\n");

		handle_print(philo, "is sleeping.");
		ft_usleep(philo->table->time_to_sleep, philo->table);

		handle_print(philo, "is thinking.");
	}
}

static
void	handle_print(t_philo *philo, const char *str)
{
	if (sem_wait(philo->table->sem_write) == -1)
		handle_exit(philo->table, "Error semaphore write wait\n");
	printf("%lld\t#%d   %s\n", get_time_ms() - philo->table->start_time, philo->id, str);
	if (sem_post(philo->table->sem_write) == -1)
		handle_exit(philo->table, "Error semaphore write post\n");
}
