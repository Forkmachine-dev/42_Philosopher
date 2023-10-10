#ifndef PHILO_H
#define PHILO_H

#define nullptr NULL
#define PH_SUCCESS 0
#define PH_FAILED 1
#define PH_FAILED_ALLOC 2
#define PH_FAILED_MUTEX_INIT 3
#define PH_FAILED_THREAD_CREATE 4
#define PH_FAILED_INVALID_ARGS 5

#define PH_PRINT_THINK 0
#define PH_PRINT_EAT 1
#define PH_PRINT_SLEEP 2

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_sim_data t_sim_data;
typedef struct s_philosopher
{
	pthread_t philo_thread;
	int id;
	t_sim_data *data;
	
} t_philosopher;

typedef struct s_sim_data
{
	int entities_count ;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int mealsCount;
	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
	struct timeval start_time;
	t_philosopher *philos;
}			t_sim_data;



int	ft_atoi(const char *nptr);
#endif 