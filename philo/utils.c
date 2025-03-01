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

void	print_status(t_philo *philo, char *stat)
{
	long long	t_s;

	pthread_mutex_lock(&philo->table->print_lock);
	t_s = get_t_in_ms() - philo->table->start_time;
	if (!sim_should_stop(philo->table))
		printf("%lld %d %s\n", t_s, philo->id, stat);
	pthread_mutex_unlock(&philo->table->print_lock);
}

int	sim_should_stop(t_table *table)
{
	pthread_mutex_lock(&table->sim_lock);
	if (table->stop_simulation)
	{
		pthread_mutex_unlock(&table->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->sim_lock);
	return (0);
}