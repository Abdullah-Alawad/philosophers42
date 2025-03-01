#include "philo.h"

void	*control_death(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!sim_should_stop(table))
	{
		i = 0;
		while (i < table->philos_num)
		{
			pthread_mutex_lock(&table->sim_lock);
			if (get_t_in_ms() - table->philos[i].last_eat > table->time_to_die)
			{
				table->stop_simulation = 1;
				pthread_mutex_unlock(&table->sim_lock);
				print_status(&table->philos[i], "died");
				return (NULL);
			}
			pthread_mutex_unlock(&table->sim_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}