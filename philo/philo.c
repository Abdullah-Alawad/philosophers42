#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	
}