#include "philo.h"

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a left fork");
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a right fork");
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a left fork");
	}
	pthread_mutex_lock(&philo->table->sim_lock);
	philo->last_eat = get_t_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->sim_lock);
	print_status(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	*philo_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!sim_should_stop(philo->table))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}