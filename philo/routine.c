/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:18 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:14:20 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "is thinking", YELLOW);
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(500);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "is sleeping", BLUE);
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	if (sim_should_stop(philo->table))
		return ;
	if (philo->id % 2 == 0)
	{
		if (!lock_philo_1(philo))
			return ;
	}
	else
	{
		if (!lock_philo_2(philo))
			return ;
	}
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "has taken a right fork", RESET);
	print_status(philo, "has taken a left fork", RESET);
	print_status(philo, "is eating", GREEN);
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->sim_lock);
	philo->last_eat = get_t_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->sim_lock);
	custom_sleep(philo, philo->table->time_to_eat);
	unlock_philo(philo);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (!sim_should_stop(philo->table))
	{
		if (sim_should_stop(philo->table))
			break ;
		philo_eat(philo);
		if (sim_should_stop(philo->table))
			break ;
		philo_sleep(philo);
		if (sim_should_stop(philo->table))
			break ;
		philo_think(philo);
		if (sim_should_stop(philo->table))
			break ;
	}
	return (NULL);
}
