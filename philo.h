/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:42:18 by qlefevre          #+#    #+#             */
/*   Updated: 2023/02/24 17:42:22 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				life;
	int				nu_philo;
	size_t			must_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			simbegin;
	pthread_mutex_t	m_life;
	pthread_mutex_t	msg;
	pthread_mutex_t	m_must_eat;
}t_data;

typedef struct s_fork
{
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}t_fork;

typedef struct s_philo
{
	int				id;
	int				count_meal;
	size_t			last_meal;
	pthread_t		philo;
	pthread_mutex_t	my_fork;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	m_nu_meal;
	t_data			*data;
	t_fork			fork;

}t_philo;

/* init.c */
t_data		init_data(char **argv, t_data data);
t_philo		*init_philo(t_philo *p, t_data *data);
t_philo		*init_fork(t_philo *p, t_data *data);

/* simulation.c */
void		*routine(void *arg);
int			watch(t_philo *p, t_data data);
int			launch_sim(t_philo *p, t_data data);
void		ft_set_life(t_philo p, t_data data);
int			eat(t_philo *p);

/* thread.c */
int			init_thread(t_philo *p, size_t nu);
int			join_thread(t_philo *p, size_t nu);

/* check.c */
int			check_args(int argc, char **argv, t_data *data);
int			check_nu_meal(t_philo *p, int nu);
int			check_isdigit(char **argv);

/* free.c */
int			destroy_mutex(t_philo *p, t_data data);

/* utils.c */
size_t		ft_atoi(const char *nptr);
size_t		get_time(void);
void		action_msg(t_philo p, char *message);
int			ft_isdigit(int c);
void		ft_usleep(size_t wait);

#endif
