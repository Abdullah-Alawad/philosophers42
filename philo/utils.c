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
	if (nptr[i] == '\0')
		return (res * sign);
	else
		return (-1);
}

long long	get_t_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
	return (0);
}

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
		usleep(200);
		elapsed_time = get_t_in_ms() - start_time;
	}
}
