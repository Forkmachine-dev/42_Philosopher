/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:16:48 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/10/23 13:17:04 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*left_fork(t_philosopher *ph)
{
	int	id;

	id = ph->id;
	if (id == ph->data->entities_count - 1)
		return (ph->data->forks);
	return (ph->data->forks + id + 1);
}
