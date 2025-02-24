#include "philo.h"

int	init_forks(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthead_mutex_t)
		* table->philos_num);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->philos_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}	
}

int	init_table(t_table *table, int ac, char **av)
{
	struct timeval	tv;

	table->philos_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->stop_simulation = 0;
	if (table->philos_num < 2 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (0);
	if (gettimeofday(&tv, NULL) == 0)
		table->start_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	else
		return (0);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) < 0)
			return (0);
		table->meals_num = ft_atoi(av[5]);
	}
	else
		table->meals_num = 0;
	if (!init_forks(table))
		return (0);
	init_philos(table);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	
}