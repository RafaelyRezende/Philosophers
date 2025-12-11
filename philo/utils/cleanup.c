#include "philo.h"

void	cleanup_table(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
