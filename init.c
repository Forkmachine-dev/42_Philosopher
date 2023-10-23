/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:05:13 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 17:41:00 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_sim_data *data)
{
	int	i;

	i = -1;
	data->philos = 
		(t_philosopher *)malloc(sizeof(t_philosopher) * data->entities_count);
	if (!data->philos)
	{
		assert(PH_FAILED_ALLOC);
		return (PH_FAILED_ALLOC);
	}
	while (++i < data->entities_count)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].meals_eaten = data->mealsCount;
		data->philos[i].last_time_ate = 0;
		if (assert(pthread_create(&data->philos[i].philo_thread, 
					nullptr, life, &data->philos[i])) != PH_SUCCESS)
			return (PH_FAILED_THREAD_CREATE);
		if (i > 100)
			usleep(i);
		else 
			usleep(80);
	}
	return (PH_SUCCESS);
}

int	init_mutexes(t_sim_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) 
			* data->entities_count);
	if (!data->forks)
		return (PH_FAILED_ALLOC);
	while (i < data->entities_count)
	{
		if (assert(pthread_mutex_init(&data->forks[i], nullptr)) != PH_SUCCESS)
			return (PH_FAILED_MUTEX_INIT);
		i++;
	}
	if (assert(pthread_mutex_init(&data->mutex_lock, nullptr)) != PH_SUCCESS)
		return (PH_FAILED_MUTEX_INIT);
	return (PH_SUCCESS);
}

int	init(t_sim_data *data)
{
	if (assert(init_mutexes(data)) != PH_SUCCESS)
		return (PH_FAILED);
	if (assert(init_philosophers(data)) != PH_SUCCESS)
		return (PH_FAILED);
	return (PH_SUCCESS);
}

int	fill_args(int ac, char **av, t_sim_data *data)
{
	if (ac < 4 || ac > 5 || guard(ac, av) != PH_SUCCESS)
		return (PH_FAILED_INVALID_ARGS);
	data->entities_count = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->eating_philos_max = data->entities_count;
	if (ac == 5)
		data->mealsCount = ft_atoi(av[4]);
	else 
		data->mealsCount = -1;
	data->should_stop = false;
	if ((data_is_valid(data, ac)) != PH_SUCCESS)
		return (PH_FAILED_INVALID_ARGS);
	gettimeofday(&data->start_time, nullptr);
	return (0);
}
