/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:09:42 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:10:05 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (check_args(argc, argv) != 1)
		return (2);
	data = init_data(argc, argv);
	if (data->nu_philo == 1)
		return (one_philo(*data->philo, data), 0);
	// pthread_mutex_lock(&data->m_life);
	// printf("life = %d\n", data->life);
	// pthread_mutex_unlock(&data->m_life);
	// action_msg(*data->philo[1], "say hi");
	launch_sim(*data->philo, data);
	destroy_mutex(*data->philo, data);
	return (0);
}

void	one_philo(t_philo *p, t_data *data)
{
	action_msg(p[0], "has taken a fork");
	ft_usleep(data->time_to_die);
	action_msg(p[0], "died");
	destroy_mutex(p, data);
}

t_philo	*get_last_meal(t_philo *p)
{
	pthread_mutex_lock(&p->m_meal);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->m_meal);
	return (p);
}
