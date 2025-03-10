#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	controller;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	if (pthread_create(&controller, NULL, &control_death, &table) != 0)
		return (1);
	pthread_join(controller, NULL);
	i = 0;
	while (i < table.philos_num)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	clean_table(&table);
}
