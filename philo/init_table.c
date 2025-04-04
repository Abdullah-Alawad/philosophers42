/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:13:55 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:13:58 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table)
{
	int	i;

	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philos_num);
	if (!table->philos)
		return (0);
	i = 0;
	while (i < table->philos_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_eat = table->start_time;
		table->philos[i].table = table;
		table->philos[i].left_f = &table->forks[i];
		table->philos[i].right_f = &table->forks[(i + 1) % table->philos_num];
		table->philos[i].meals_eaten = 0;
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_routine, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
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
	if (pthread_mutex_init(&table->print_lock, NULL) != 0
		|| pthread_mutex_init(&table->sim_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_table(t_table *table, int ac, char **av)
{
	struct timeval	tv;

	table->philos_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->stop_simulation = 0;
	if (table->philos_num < 1 || table->time_to_die < 0
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
		table->meals_required = ft_atoi(av[5]);
	}
	else
		table->meals_required = -1;
	if (!init_forks(table) || !init_philos(table))
		return (0);
	return (1);
}
