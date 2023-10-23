#ifndef PHILO_H
#define PHILO_H

#define nullptr NULL
#define PH_SUCCESS 0
#define PH_FAILED 1
#define PH_FAILED_ALLOC 2
#define PH_FAILED_MUTEX_INIT 3
#define PH_FAILED_THREAD_CREATE 4
#define PH_FAILED_INVALID_ARGS 5

#define PH_PRINT_THINK 6
#define PH_PRINT_EAT 7
#define PH_PRINT_SLEEP 8
#define PH_PRINT_DEATH 9
#define PH_PRINT_TAKE_FORK 10

#define true 1
#define false 0

#define bool int

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_sim_data t_sim_data;
typedef struct s_philosopher
{
	pthread_t philo_thread;
	unsigned long long last_time_ate;
	bool is_running;
	int id;
	int meals_eaten;
	t_sim_data *data;
} t_philosopher;

typedef struct s_sim_data
{
	int entities_count ;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int mealsCount;
	bool should_stop;
	int eating_philos_max;
	pthread_mutex_t *forks;
	pthread_mutex_t mutex_lock;
	struct timeval start_time;
	t_philosopher *philos;
}			t_sim_data;

void	*life(void *arg);
int		assert (int error);
int		init(t_sim_data *data);
void	check_loop(t_sim_data *data);
int		fill_args(int ac, char **av, t_sim_data *data);
void	lock_and_print(t_philosopher *ph, int what);
unsigned	long long	get_time_diff(struct timeval start_time);
void	msleep(int tts, t_sim_data *data);
void	ms_sleep(unsigned long long msec, t_philosopher* ph);
void	*philo_basic_life(void *philo);
int	ft_isdigit(int c);
int	data_is_valid(t_sim_data *data, int ac);
int	guard(int ac, char **av);
pthread_mutex_t	*left_fork(t_philosopher *ph);

int	ft_atoi(const char *nptr);
int	ft_usleep(useconds_t time);
#endif 