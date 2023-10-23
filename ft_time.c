/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:51:23 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 18:25:37 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time_diff(struct timeval start_time)
{
	long long		s_milliseconds;
	struct timeval	current_time;
	long long		c_milliseconds;

	s_milliseconds = (long long)((start_time.tv_sec) * 1000)
		+ (long long)(start_time.tv_usec) / 1000;
	gettimeofday(&current_time, nullptr);
	c_milliseconds = (long long)((current_time.tv_sec) * 1000)
		+(long long)(current_time.tv_usec) / 1000;
	return (c_milliseconds - s_milliseconds);
}

void	msleep(int tts, t_sim_data *data)
{
	struct timeval	ct;
	long int		start_time;
	long int		current_time;

	gettimeofday(&ct, NULL);
	start_time = ((ct.tv_sec * 1e6) + ct.tv_usec);
	current_time = 0;
	while (current_time <= tts * 1000)
	{
		usleep(100);
		gettimeofday(&ct, NULL);
		current_time = ((ct.tv_sec * 1e6) + ct.tv_usec);
		current_time -= start_time;
		pthread_mutex_lock(&data->mutex_lock);
		if (data->should_stop)
		{
			pthread_mutex_unlock(&data->mutex_lock);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_lock);
	}
}
