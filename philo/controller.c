#include "philo.h"

void	*control_death(void *arg)
{
	t_table	*table;
	int		i;
	int		all_philos;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		all_philos = 0;
		while (i < table->philos_num)
		{
			pthread_mutex_lock(&table->sim_lock);
			if (get_t_in_ms() - table->philos[i].last_eat >= table->time_to_die)
			{
				pthread_mutex_lock(&table->print_lock);
				print_status(&table->philos[i], "died", RED);
				table->stop_simulation = 1;
				pthread_mutex_unlock(&table->print_lock);
				pthread_mutex_unlock(&table->sim_lock);
				return (NULL);
			}
			if (table->meals_required > 0
				&& table->philos[i].meals_eaten >= table->meals_required)
				all_philos++;
			pthread_mutex_unlock(&table->sim_lock);
			i++;
		}
		if (all_philos == table->philos_num)
		{
			pthread_mutex_lock(&table->sim_lock);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->sim_lock);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
