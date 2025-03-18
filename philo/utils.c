/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:26 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:14:27 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

long long	get_t_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
/*
void print_status(t_philo *philo, char *stat, char *color)
{
    long long elapsed;
    long long time_interval;


	if (!ft_strncmp(stat, "eating", 100))
		time_interval = philo->table->time_to_eat;
	else if (!ft_strncmp(stat, "sleeping", 100))
		time_interval = philo->table->time_to_sleep;
	else if (!ft_strncmp(stat, "died", 100))
		time_interval = philo->table->time_to_die;
	else
		time_interval = philo->table->time_to_eat;
	elapsed = get_t_in_ms() - philo->table->start_time;
	if (time_interval > 0)
		elapsed = ((elapsed + (time_interval / 2)) / time_interval) * time_interval;

    printf("%s%lld %d %s\n"RESET, color, elapsed, philo->id, stat);
}
	*/

void	print_status(t_philo *philo, char *stat, char *color)
{
	printf("%s%lld %d %s\n"RESET, color,
		get_t_in_ms() - philo->table->start_time, philo->id, stat);
}

int	sim_should_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->sim_lock);
	stop = table->stop_simulation;
	pthread_mutex_unlock(&table->sim_lock);
	return (stop);
}

void	custom_sleep(t_philo *philo, int sleep_time_ms)
{
	long long	start_time;
	long long	elapsed_time;

	start_time = get_t_in_ms();
	elapsed_time = 0;
	while (elapsed_time < sleep_time_ms)
	{
		if (sim_should_stop(philo->table))
			return ;
		usleep(500);
		elapsed_time = get_t_in_ms() - start_time;
	}
}

void ft_usleep(long long duration_ms)
{
    long long start_time = get_t_in_ms();
    while ((get_t_in_ms() - start_time) < duration_ms)
        usleep(400); // Small sleeps to reduce CPU usage
}
