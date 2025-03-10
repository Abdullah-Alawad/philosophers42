#include "philo.h"

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_num)
	{
		if (&table->forks[i])
			pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->sim_lock);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}
