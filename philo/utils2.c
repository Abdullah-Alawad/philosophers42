/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:33 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:14:36 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_philo_1(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->left_f);
		return (0);
	}
	pthread_mutex_lock(philo->right_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	return (1);
}

int	lock_philo_2(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	pthread_mutex_lock(philo->left_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		return (0);
	}
	return (1);
}

void	unlock_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
	else
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
}

int	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!lock_philo_1(philo))
			return (0);
	}
	else
	{
		if (!lock_philo_2(philo))
			return (0);
	}
	return (1);
}

void	print_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "has taken a right fork", AQUA);
	print_status(philo, "has taken a left fork", AQUA);
	print_status(philo, "is eating", GREEN);
	pthread_mutex_unlock(&philo->table->print_lock);
}
