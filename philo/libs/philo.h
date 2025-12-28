#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <limits.h>

# ifndef MAX_PHILO
#  define MAX_PHILO 200
# endif

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long				philo_count;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				must_eat_count;
	long long			start_time;
	int					sim_running;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		sim_lock;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}	t_table;

/* Validation & Parsing */
long		ft_atol_positive(const char *nptr);
int			parse_philos(int argc, char **argv, t_table *table);
int			ft_isspace(char s);
void		ft_putstr_fd(int fd, char *buff);

// Init & Cleanup
int			initialize_simulation(t_table *table);
void		cleanup_table(t_table *table, char *msg, int exit_code);

// Utils
long long	get_time_ms(void);
void		ft_usleep(long time_in_ms, t_table *table);
void		*routine(void *arg);

#endif
