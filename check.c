/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:51:33 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 12:57:01 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	guard(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (1)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (PH_FAILED_INVALID_ARGS);
			j++;
		}
		i++;
		if (i == ac)
			break ;
	}
	return (PH_SUCCESS);
}

int	data_is_valid(t_sim_data *data, int ac)
{
	if (!data)
		return (PH_FAILED_ALLOC);
	if (data->eating_philos <= 0)
		return (PH_FAILED_INVALID_ARGS);
	if (data->time_to_die <= 0)
		return (PH_FAILED_INVALID_ARGS);
	if (data->time_to_eat <= 0)
		return (PH_FAILED_INVALID_ARGS);
	if (data->time_to_sleep <= 0 && ac == 5)
		return (PH_FAILED_INVALID_ARGS);
	return (PH_SUCCESS);
}

bool	check_death(t_philosopher *ph)
{
	unsigned long long	ct;
	unsigned long long	last_time_ate;

	if (!ph->is_running)
		return (false);
	pthread_mutex_lock(&ph->data->check_death_mutex);
	last_time_ate = ph->last_time_ate;
	pthread_mutex_unlock(&ph->data->check_death_mutex);
	ct = get_time_diff(ph->data->start_time);
	if (ct - last_time_ate >= (unsigned long long)ph->data->time_to_die)
	{
		lock_and_print(ph, PH_PRINT_DEATH);
		return (true);
	}
	return (false);
}

bool	all_eat_max(t_sim_data *data)
{
	int	eating_philos;

	if (data->mealsCount == -1)
		return (false);
	pthread_mutex_lock(&data->check_eat_mutex);
	eating_philos = data->eating_philos;
	pthread_mutex_unlock(&data->check_eat_mutex);
	if (eating_philos <= 0)
	{
		data->should_stop = (true);
		return (true);
	}
	return (false);
}

void	check_loop(t_sim_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (true)
	{
		if (check_death(&data->philos[i]) || all_eat_max(data))
		{
			while (j < data->entities_count)
			{
				pthread_mutex_unlock(&data->forks[j]);
				j++;
			}
			break ;
		}
		i++;
		if (i == data->entities_count)
			i = 0;
		usleep(10);
	}
}