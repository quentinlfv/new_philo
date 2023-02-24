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
	p = init_philo(p, &data);
	launch_sim(p, data);
	destroy_mutex(p, data);
	return (0);
}
