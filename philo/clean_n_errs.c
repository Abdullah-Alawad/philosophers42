/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_n_errs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:13:47 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:13:49 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
