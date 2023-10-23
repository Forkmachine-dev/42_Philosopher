/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:18:11 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 13:32:32 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_sim_data *data)
{
	int	i;

	i = 0;
	while (i < data->entities_count)
	{
		pthread_join(data->philos[i].philo_thread, nullptr);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_sim_data	sim_data;

	if (assert(fill_args(ac - 1, ++av, &sim_data)) != PH_SUCCESS)
		return (1);
	if (init(&sim_data) != PH_SUCCESS)
		return (1);
	check_loop(&sim_data);
	wait_threads(&sim_data);
	return (0);
}
