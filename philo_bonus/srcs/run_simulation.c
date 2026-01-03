#include "philo_bonus.h"

void	start_simulation(t_table *table)
{
	int		i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].pid = fork();
		if (table->philos[i].pid == -1)
			handle_exit(table, "Error create fork.\n");
		if (table->philos[i].pid == 0)
		{
			table->philos[i].last_meal = table->start_time;
			routine(&table->philos[i]);
			handle_exit(table, NULL);
		}
		i++;
	}
}

void	handle_exit(t_table *table, const char *str)
{
	int	status;

	if (str)
	{
		printf("%s", str);
		status = 1;
	}
	else
		status = 0;
	if (sem_close(table->sem_forks) == -1 && str)
		status += 2;
	if (sem_close(table->sem_write) == -1 && str)
		status += 4;
	if (sem_close(table->sem_stop) == -1 && str)
		status += 8;
	exit(status);
}
