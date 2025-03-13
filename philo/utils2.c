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

void	lock_philo_1(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->left_f);
		return ;
	}
	pthread_mutex_lock(philo->right_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return ;
	}
}

void	lock_philo_2(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->right_f);
		return;
	}
	pthread_mutex_lock(philo->left_f);
	if (sim_should_stop(philo->table))
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		return;
	}
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

void	ft_usleep(long long time)
{
	long long	start;

	start = get_t_in_ms();
	while (get_t_in_ms() - start < time)
		usleep(100);
}

void	custom_sleep(t_philo *philo, int sleep_time_ms)
{
    long long start_time;
    long long elapsed_time;

	start_time = get_t_in_ms();
	elapsed_time = 0;
	while (elapsed_time < sleep_time_ms)
	{
		if (sim_should_stop(philo->table))
			return ;
		usleep(1000);
		elapsed_time = get_t_in_ms() - start_time;
	}
}
