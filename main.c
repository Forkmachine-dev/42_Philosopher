/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:18:11 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 21:53:29 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_sim_data *data)
{
	int	i;

	i = 0;
	while (i < data->entities_count)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
}

int	free_all(t_sim_data *data)
{
	int	i;

	i = -1;
	while (++i < data->entities_count)
		if (pthread_mutex_destroy(&data->forks[i++]))
			return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&data->mutex_lock))
		return (EXIT_FAILURE);
	free(data->philos);
	free(data->forks);
	return (PH_SUCCESS);
}

int	main(int ac, char **av)
{
	t_sim_data	sim_data;

	if (assert(fill_args(ac - 1, ++av, &sim_data)) != PH_SUCCESS)
		return (EXIT_FAILURE);
	if (init(&sim_data) != PH_SUCCESS)
		return (EXIT_FAILURE);
	check_loop(&sim_data);
	wait_threads(&sim_data);
	if (free_all(&sim_data) != PH_SUCCESS)
		return (EXIT_FAILURE);
	return (0);
}
