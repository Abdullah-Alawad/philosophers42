#include "philo.h"

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->sim_lock);
	free(table->forks);
	free(table->philos);
}