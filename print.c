/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:18:47 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 18:18:21 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err(char *msg)
{
	printf("Error: %s\n", msg);
}

int	assert(int error)
{
	if (!error)
		return (PH_SUCCESS);
	if (error == PH_FAILED)
		err("Unknown Issue");
	else if (error == PH_FAILED_ALLOC)
		err("Failed to allocate memory");
	else if (error == PH_FAILED_INVALID_ARGS)
		err("Invalid Argumants");
	else if (error == PH_FAILED_MUTEX_INIT)
		err("Failed to initialize a mutex");
	else if (error == PH_FAILED_THREAD_CREATE)
		err("Failed to create a thread");
	return (PH_FAILED);
}

void	lock_and_print(t_philosopher *ph, int what)
{
	unsigned long long	t;

	t = get_time_diff(ph->data->start_time);
	pthread_mutex_lock(&ph->data->mutex_lock);
	if (ph->data->should_stop)
	{
		pthread_mutex_unlock(&ph->data->mutex_lock);
		return ;
	}
	if (what == PH_PRINT_THINK)
		printf("%lld %d is thinking\n", t, ph->id + 1);
	else if (what == PH_PRINT_EAT)
		printf("%lld %d is eating\n", t, ph->id + 1);
	else if (what == PH_PRINT_SLEEP)
		printf("%lld %d is sleeping\n", t, ph->id + 1);
	else if (what == PH_PRINT_TAKE_FORK)
		printf("%lld %d has taken a fork\n", t, ph->id + 1);
	pthread_mutex_unlock(&ph->data->mutex_lock);
}
