/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:51:05 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 21:55:51 by mel-akhd         ###   ########.fr       */
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
	lock_and_print(ph, PH_PRINT_EAT);
	pthread_mutex_lock(&ph->data->mutex_lock);
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	pthread_mutex_unlock(&ph->data->mutex_lock);
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
	lock_and_print(ph, PH_PRINT_EAT);
	pthread_mutex_lock(&ph->data->mutex_lock);
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	pthread_mutex_unlock(&ph->data->mutex_lock);
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
	if (ph->data->meals_count > 0 && ph->meals_eaten != 10e6)
		ph->meals_eaten--;
}

void	sleep_ph(t_philosopher *ph)
{
	lock_and_print(ph, PH_PRINT_SLEEP);
	msleep(ph->data->time_to_sleep, ph->data);
}

void	*life(void *arg)
{
	t_philosopher	*ph;

	ph = (t_philosopher *)arg;
	pthread_mutex_lock(&ph->data->mutex_lock);
	ph->last_time_ate = get_time_diff(ph->data->start_time);
	ph->is_running = TRUE;
	while (ph->data->should_stop == FALSE) 
	{
		pthread_mutex_unlock(&ph->data->mutex_lock);
		lock_and_print(ph, PH_PRINT_THINK);
		eat(ph);
		sleep_ph(ph);
		pthread_mutex_lock(&ph->data->mutex_lock);
		if (ph->meals_eaten == 0)
		{
			ph->data->eating_philos_max--;
			ph->meals_eaten = -10e6;
		}
	}
	ph->is_running = FALSE;
	pthread_mutex_unlock(&ph->data->mutex_lock);
	return (NULL);
}
