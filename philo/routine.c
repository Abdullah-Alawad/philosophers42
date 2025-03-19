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
	long	t_left;

	pthread_mutex_lock(&philo->table->sim_lock);
	t_left = get_t_in_ms() - philo->last_eat;
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "is thinking", YELLOW);
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_unlock(&philo->table->sim_lock);
	if (t_left > philo->table->time_to_die * 0.75)
		usleep(100);
	else
		usleep(300);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	print_status(philo, "is sleeping", BLUE);
	pthread_mutex_unlock(&philo->table->print_lock);
	custom_sleep(philo, philo->table->time_to_sleep);
}


void	philo_eat(t_philo *philo)
{
	long	t_left;

	if (sim_should_stop(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->sim_lock);
	t_left = (get_t_in_ms() - philo->last_eat);
	pthread_mutex_unlock(&philo->table->sim_lock);
	if (t_left > philo->table->time_to_die * 0.75)
		usleep(300);
	if (!lock_forks(philo))
		return ;
	print_eat(philo);
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
		usleep(200);
	while (!sim_should_stop(philo->table))
	{
		if (philo->table->philos_num == 1)
			break ;
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
