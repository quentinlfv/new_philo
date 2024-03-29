/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:20:22 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:20:25 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	n;
	int		sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		n = n * 10 + (nptr[i] - 48);
		i++;
	}
	return (n * sign);
}

size_t	get_time(void)
{
	struct timeval	get_time;
	size_t			time;

	gettimeofday(&get_time, NULL);
	time = get_time.tv_sec * 1000 + get_time.tv_usec / 1000;
	return (time);
}

void	action_msg(t_philo *p, char *message)
{
	size_t	time;

	pthread_mutex_lock(&p->data->msg);
	time = get_time();
	if (is_philo_dead(p) == false)
	{
		printf("%ld    %d %s\n", time - p->data->simbegin, p->id, message);
		pthread_mutex_unlock(&p->data->msg);
	}
	else
		pthread_mutex_unlock(&p->data->msg);

}

void	ft_usleep(size_t wait)
{
	struct timeval	get_time;
	size_t			time;

	gettimeofday(&get_time, NULL);
	time = get_time.tv_sec * 1000 + get_time.tv_usec / 1000;
	while (time + wait > (size_t)get_time.tv_sec * 1000
		+ (size_t)get_time.tv_usec / 1000)
	{
		usleep(50);
		gettimeofday(&get_time, NULL);
	}
}
