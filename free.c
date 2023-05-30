/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:06:56 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:07:04 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	destroy_mutex(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->m_life);
	pthread_mutex_destroy(&data->msg);
	pthread_mutex_destroy(&data->m_must_eat);
	i = 0;
	while (i < data->nu_philo)
	{
		free(data->philo[i]);
		// pthread_mutex_destroy(&p[i].my_fork);
		// pthread_mutex_destroy(&p[i].m_meal);
		// pthread_mutex_destroy(&p[i].m_nu_meal);
		i++;
	}
	free(data->philo);
	free(data);
	return (1);
}
