/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:51:05 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 13:17:49 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_with_left(t_philosopher *ph)
{
	int	id;

	id = ph->id;
	pthread_mutex_lock(left_fork(ph));
	lock_and_print(ph, PH_PRINT_TAKE_FORK);
	pthread_mutex_lock(&ph->data->forks[id]);
	lock_and_print(ph, PH_PRINT_TAKE_FORK);
	pthread_mutex_lock(&ph->data->check_death_mutex);
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	pthread_mutex_unlock(&ph->data->check_death_mutex);
	lock_and_print(ph, PH_PRINT_EAT);
	msleep(ph->data->time_to_eat, ph->data);
	pthread_mutex_unlock(left_fork(ph));
	pthread_mutex_unlock(&ph->data->forks[id]);
}

void	eat_with_right(t_philosopher *ph)
{
	int	id;

	id = ph->id;
	usleep(100);
	pthread_mutex_lock(&ph->data->forks[id]);
	lock_and_print(ph, PH_PRINT_TAKE_FORK);
	pthread_mutex_lock(left_fork(ph));
	lock_and_print(ph, PH_PRINT_TAKE_FORK);
	pthread_mutex_lock(&ph->data->check_death_mutex);
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	pthread_mutex_unlock(&ph->data->check_death_mutex);
	lock_and_print(ph, PH_PRINT_EAT);
	msleep(ph->data->time_to_eat, ph->data);
	pthread_mutex_unlock(&ph->data->forks[id]);
	pthread_mutex_unlock(left_fork(ph));
}

void	eat(t_philosopher *ph)
{
	int	id;

	id = ph->id;
	if (id % 2)
		eat_with_left(ph);
	else 
		eat_with_right(ph);
	if (ph->data->mealsCount > 0)
		ph->meals_eaten--;
}

void	sleep_ph(t_philosopher *ph)
{
	if (ph->data->should_stop)
		return ;
	lock_and_print(ph, PH_PRINT_SLEEP);
	msleep(ph->data->time_to_sleep, ph->data);
}

void	*life(void *arg)
{
	t_philosopher	*ph;

	ph = (t_philosopher *)arg;
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	ph->is_running = true;
	while (!ph->data->should_stop && ph->meals_eaten) 
	{
		lock_and_print(ph, PH_PRINT_THINK);
		eat(ph);
		sleep_ph(ph);
	}
	pthread_mutex_lock(&ph->data->check_eat_mutex);
	ph->data->eating_philos--;
	pthread_mutex_unlock(&ph->data->check_eat_mutex);
	ph->is_running = false;
	return (nullptr);
}
