#ifndef PHILO_C
# define PHILO_C

# include <stdio.h>
# include <stdlib.h>
# include <string.h>  // memset
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	struct s_philo	*philos;
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
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
    pthread_mutex_t *left_f;
    pthread_mutex_t *right_f;
	struct s_table	*table;
}	t_philo;

int	ft_atoi(const char *nptr);
int	init_table(t_table *table, int ac, char **av);


#endif