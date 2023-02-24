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

int	eat(t_philo *p)
{
	pthread_mutex_lock(p->fork.right);
	action_msg(*p, "has taken a fork");
	if (pthread_mutex_lock(p->fork.left) != 0)
	{
		pthread_mutex_lock(&p->data->m_life);
		if (p->data->life == 0)
		{
			pthread_mutex_unlock(&p->data->m_life);
			pthread_mutex_unlock(p->fork.right);
			return (0);
		}
		pthread_mutex_unlock(&p->data->m_life);
	}
	action_msg(*p, "has taken a fork");
	action_msg(*p, "is eating");
	pthread_mutex_lock(&p->m_meal);
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->m_meal);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_lock(&p->m_nu_meal);
	p->count_meal += 1;
	pthread_mutex_unlock(&p->m_nu_meal);
	action_msg(*p, "is sleeping");
	pthread_mutex_unlock(p->fork.right);
	pthread_mutex_unlock(p->fork.left);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0 || p->id == p->data->nu_philo)
	{
		action_msg(*p, "is thinking");
		ft_usleep(p->data->time_to_eat);
	}
	while (1)
	{
		pthread_mutex_lock(&p->data->m_life);
		if (p->data->life == 0)
		{
			pthread_mutex_unlock(&p->data->m_life);
			break ;
		}
		pthread_mutex_unlock(&p->data->m_life);
		if (!eat(p))
			return (NULL);
		ft_usleep(p->data->time_to_sleep);
		action_msg(*p, "is thinking");
	}
	return (NULL);
}

int	watch(t_philo *p, t_data data)
{
	size_t	time;
	size_t	meal;
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&p[i].m_meal);
		meal = p[i].last_meal;
		pthread_mutex_unlock(&p[i].m_meal);
		time = get_time();
		if (!check_nu_meal(p, data.nu_philo))
		{
			ft_set_life(p[i], data);
			break ;
		}
		if (time - (meal + p[i].data->time_to_die) < data.simbegin)
		{
			action_msg(p[i], "died");
			ft_set_life(p[i], data);
			break ;
		}
		i = (i + 1) % data.nu_philo;
	}
	return (1);
}

int	launch_sim(t_philo *p, t_data data)
{
	init_thread(p, data.nu_philo);
	watch(p, data);
	join_thread(p, data.nu_philo);
	return (1);
}

void	ft_set_life(t_philo p, t_data data)
{
	pthread_mutex_lock(&data.m_life);
	p.data->life = 0;
	pthread_mutex_unlock(&data.m_life);
}
