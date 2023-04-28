/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:05:55 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:06:01 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_nu_meal(t_philo *p, int nu)
{
	int		i;
	size_t	count;

	i = 0;
	if (p[i].data->must_eat == 0)
		return (1);
	while (i < nu)
	{
		pthread_mutex_lock(&p[i].m_nu_meal);
		count = p[i].count_meal;
		pthread_mutex_unlock(&p[i].m_nu_meal);
		pthread_mutex_lock(&p[i].data->m_must_eat);
		if ((int)count - (int)p[i].data->must_eat <= 0)
		{
			pthread_mutex_unlock(&p[i].data->m_must_eat);
			break ;
		}
		pthread_mutex_unlock(&p[i].data->m_must_eat);
		if (p[i].id == nu)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv, t_data *data)
{
	if (argc == 5)
		data->must_eat = 0;
	else if (argc == 6)
		data->must_eat = 1;
	else if (argc > 6)
	{
		perror("too much arguments");
		return (0);
	}
	if (!check_isdigit(argv))
		return (0);
	return (1);
}

int	check_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
