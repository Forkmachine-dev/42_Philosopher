#include "philo.h"


void err(char *msg)
{
	printf("Error: %s\n", msg);
}

int fill_args(int ac, char **av, t_sim_data *data)
{
	if(ac < 4 || ac > 5)
		return PH_FAILED_INVALID_ARGS;
	data->entities_count = ft_atoi(av[0]);
	data->time_to_die =  ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if(ac == 5)
		data->noftephm_eat = ft_atoi(av[4]);
	else 
		data->noftephm_eat = 0;
	data->value = 0;
	return (0);
}

int assert (int error)
{
	if(!error)
		return PH_SUCCESS;
	if(error == PH_FAILED)
		err("Unknown Issue");
	else if (error == PH_FAILED_ALLOC)
		err("Failed to allocate memory");
	else if (error == PH_FAILED_INVALID_ARGS)
		err("Invalid Argumants");
	else if (error == PH_FAILED_MUTEX_INIT)
		err("Failed to initialize a mutex");
	else if (error == PH_FAILED_THREAD_CREATE)
		err("Failed to create a thread");
	return PH_FAILED;
}
void print_data(t_sim_data *data)
{
	printf("Philos: %d\n",data->entities_count);
	printf("Forks: %d\n",data->entities_count);
	printf("Time To Die: %d\n",data->time_to_die);
	printf("Time To Eat: %d\n",data->time_to_eat);
	printf("Time To Sleep: %d\n",data->time_to_sleep);
	printf("Number Of Times Each Philo Must Eat: %d\n",data->noftephm_eat);

}



void	*life(void *arg)
{
	t_philosopher *ph = (t_philosopher *)arg;
	for (size_t i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&ph->data->write_lock);
		ph->data->value++;
		pthread_mutex_unlock(&ph->data->write_lock);
	}
	
	return (nullptr);
}

int init_philosophers(t_sim_data *data)
{
	int i;

	i = 0;
	data->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * data->entities_count);
	if(!data->philos)
	{
		assert(PH_FAILED_ALLOC);
		return PH_FAILED_ALLOC;
	}

	while (i < data->entities_count)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		if(assert(pthread_create(&data->philos[i].philo_thread, nullptr,life, &data->philos[i])) != PH_SUCCESS)
			return PH_FAILED_THREAD_CREATE;
		i++;
	}
	return PH_SUCCESS;
}
int init_mutexes(t_sim_data *data)
{
	int i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->entities_count);
	if(!data->forks)
		return PH_FAILED_ALLOC;
	while (i < data->entities_count)
	{
		if(assert(pthread_mutex_init(&data->forks[i], nullptr)) != PH_SUCCESS)
			return PH_FAILED_MUTEX_INIT;
		i++;
	}
	if(assert(pthread_mutex_init(&data->write_lock, nullptr)) != PH_SUCCESS)
		return PH_FAILED_MUTEX_INIT;
	return PH_SUCCESS;
}
void wait_threads (t_sim_data *data)
{
	int i;

	i = 0;
	while (i < data->entities_count)
	{
		pthread_join(data->philos[i].philo_thread, nullptr);
		i++;
	}
}
int init(t_sim_data *data)
{
	if (assert(init_mutexes(data)) != PH_SUCCESS)
		return PH_FAILED;
	if (assert(init_philosophers(data)) != PH_SUCCESS)
		return PH_FAILED;
	return PH_SUCCESS;
}
int main(int ac, char **av)
{
	t_sim_data sim_data;
	if(assert(fill_args(ac - 1, ++av, &sim_data)) != PH_SUCCESS)
		return (1);
	print_data(&sim_data);
	if(init(&sim_data) != PH_SUCCESS)
		return (1);
	wait_threads(&sim_data);
	printf("Value is: %d\n", sim_data.value);
	return (0);
}
