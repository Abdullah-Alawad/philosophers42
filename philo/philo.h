/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalawad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:14:11 by aalawad           #+#    #+#             */
/*   Updated: 2025/03/13 14:14:13 by aalawad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define GREEN		"\033[0;32m"
# define RED		"\033[0;31m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define RESET		"\033[0m"
# define FOREVER	1

typedef struct s_table
{
	struct s_philo	*philos;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
	long long		start_time;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long long		last_eat;
	int				meals_eaten;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_table	*table;
}	t_philo;

int			ft_atoi(const char *nptr);
int			init_table(t_table *table, int ac, char **av);
long long	get_t_in_ms(void);
void		*philo_routine(void	*arg);
void		print_status(t_philo *philo, char *stat, char *color);
void		clean_table(t_table *table);
int			sim_should_stop(t_table *table);
void		*control_death(void *arg);
void		custom_sleep(t_philo *philo, int sleep_time_ms);
int			lock_philo_1(t_philo *philo);
int			lock_philo_2(t_philo *philo);
void		unlock_philo(t_philo *philo);
int			lock_forks(t_philo *philo);
void		print_eat(t_philo *philo);

#endif
