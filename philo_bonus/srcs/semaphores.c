#include "philo_bonus.h"

static int	handle_error(t_table *table, t_sem_label label);

int	initialize_table_semaphores(t_table *table)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_stop");
	table->sem_forks = sem_open("/sem_forks", \
O_CREAT, 0644, table->philo_count);
	table->sem_write = sem_open("/sem_write", O_CREAT, 0644, 1);
	table->sem_stop = sem_open("/sem_stop", O_CREAT, 0644, 1);
	if (table->sem_forks == SEM_FAILED)
		return (handle_error(table, SEM_FORKS));
	if (table->sem_write == SEM_FAILED)
		return (handle_error(table, SEM_WRITE));
	if (table->sem_stop == SEM_FAILED)
		return (handle_error(table, SEM_STOP));
	return (0);
}

void	initialize_philos(t_table *table, t_philo *philos, pid_t *pids)
{
	int	i;

	table->philos = philos;
	table->pids = pids;
	i = 0;
	while (i < table->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = 0;
		philos[i].table = table;
		i++;
	}
}

static
int	handle_error(t_table *table, t_sem_label label)
{
	printf("Error semaphore creation.\n");
	if (label == SEM_FORKS)
		return (label);
	if (label == SEM_WRITE)
	{
		sem_close(table->sem_forks);
		sem_unlink("/sem_forks");
		return (label);
	}
	if (label == SEM_STOP)
	{
		sem_close(table->sem_forks);
		sem_close(table->sem_write);
		sem_unlink("/sem_forks");
		sem_unlink("/sem_write");
		return (label);
	}
	return (SEM_ERR);
}
