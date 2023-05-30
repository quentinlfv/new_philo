/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:10:44 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:13:41 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	eat(t_philo *p)
{
	pthread_mutex_lock(p->fork.right);
	action_msg(p, "has taken a fork");
	pthread_mutex_lock(p->fork.left);
	action_msg(p, "has taken a fork");
	action_msg(p, "is eating");
	p = get_last_meal(p);
	ft_usleep(p->data->time_to_eat);
	if (is_philo_dead(p) == false)
	{
		pthread_mutex_lock(&p->m_meal);
		p->count_meal += 1;
		pthread_mutex_unlock(&p->m_meal);
	}
	action_msg(p, "is sleeping");
	pthread_mutex_unlock(p->fork.right);
	pthread_mutex_unlock(p->fork.left);
	ft_usleep(p->data->time_to_sleep);
}

void	thinking(t_philo *p)
{
	int sleep;
	sleep = p->data->time_to_eat - p->data->time_to_sleep;
	if (sleep < 0)
		sleep = sleep * (-1);
	ft_usleep((size_t)sleep);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0 || p->id == p->data->nu_philo)
	{
		action_msg(p, "is thinking");
		ft_usleep(p->data->time_to_eat);
	}
	while (is_philo_dead(p) == false)
	{
		eat(p);
		action_msg(p, "is thinking");
		thinking(p);
	}
	return (NULL);
}

int	launch_sim(t_data *data)
{
	init_philos_thread(data, data->nu_philo);
	init_death_thread(data);
	join_thread(data, data->nu_philo);
	return (1);
}
