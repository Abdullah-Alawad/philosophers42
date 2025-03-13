/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:45 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:14:48 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_table *table, int i)
{
	if (get_t_in_ms() - table->philos[i].last_eat >= table->time_to_die)
	{
		pthread_mutex_lock(&table->print_lock);
		print_status(&table->philos[i], "died", RED);
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->print_lock);
		pthread_mutex_unlock(&table->sim_lock);
		return (1);
	}
	return (0);
}

int	check_num_of_meals(t_table *table, int all_philos)
{
	if (all_philos == table->philos_num)
	{
		pthread_mutex_lock(&table->sim_lock);
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->sim_lock);
		return (1);
	}
	return (0);
}

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
			if (check_death(table, i))
				return (NULL);
			if (table->meals_required > 0
				&& table->philos[i].meals_eaten >= table->meals_required)
				all_philos++;
			pthread_mutex_unlock(&table->sim_lock);
			i++;
		}
		if (check_num_of_meals(table, all_philos))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
