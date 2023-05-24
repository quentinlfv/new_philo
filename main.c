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
	t_philo	*p;
	t_data	data;

	if (check_args(argc, argv, &data) != 1)
		return (2);
	p = NULL;
	data = init_data(argv, data);
	if (data.nu_philo == 1)
		return (one_philo(p, data), 0);
	p = init_philo(p, &data);
	launch_sim(p, data);
	destroy_mutex(p, data);
	return (0);
}

void	one_philo(t_philo *p, t_data data)
{
	p = init_philo(p, &data);
	ft_usleep(data.time_to_die);
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
