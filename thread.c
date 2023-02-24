/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:15:02 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:15:27 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init_thread(t_philo *p, size_t nu)
{
	size_t	i;

	i = 0;
	while (i < nu)
	{
		if (pthread_create(&p[i].philo, NULL, &routine, (void *)&p[i]) != 0)
		{
			perror("Failed to create thread");
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_thread(t_philo *p, size_t nu)
{
	size_t	i;

	i = 0;
	while (i < nu)
	{
		if (pthread_join(p[i].philo, NULL) != 0)
		{
			perror("Failed to join\n");
			return (0);
		}
		i++;
	}
	return (1);
}
