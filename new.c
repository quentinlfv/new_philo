// #include  "philo.h"

// void	*routine(void *arg)
// {
// 	t_philo	*p;
// 	size_t	time;

// 	p = (t_philo *)arg;
// 	if (p->id % 2 == 0 || p->id == p->data->nu_philo)
// 	{
// 		action_msg(*p, "is thinking");
// 		ft_usleep(p->data->time_to_eat);
// 	}
// 	time = get_time();
// 	pthread_mutex_lock(&p->data->m_life);
// 	if (p->data->life == 0)
// 	{
// 		pthread_mutex_unlock(&p->data->m_life);
// 		return (NULL);
// 	}
// 	if (time - p->data->simbegin > p->data->time_to_die)
// 	{
// 		action_msg(*p, "died");
// 		p->data->life = 0;
// 		pthread_mutex_unlock(&p->data->m_life);
// 		return (NULL);
// 	}
//     pthread_mutex_unlock(&p->data->m_life);
// 	eat(p);
// 	return (NULL);
// }

// int	eat(t_philo *p)
// {
// 	pthread_mutex_lock(&p->data->m_life);
// 	while(p->data->life != 0)
// 	{
// 		pthread_mutex_unlock(&p->data->m_life);
// 		if (take_right_fork(p) == FAILURE)
//             break;
// 		if (take_left_fork(p) == FAILURE)
//             break;
// 		if (eating(p) == FAILURE)
//             break;
// 		if (sleeping(p) == FAILURE)
//             break;
// 		action_msg(*p, "is thinking");
// 		pthread_mutex_lock(&p->data->m_life);
// 	}
// 	pthread_mutex_lock(&p->data->m_life);
//     return (0);
// }

// int	take_right_fork(t_philo *p)
// {
// 	size_t time;

// 	while (1)
// 	{
// 		if (pthread_mutex_lock(p->fork.right) ==  0)
// 		{
// 			action_msg(*p, "has taken a fork");
// 			return (SUCCESS);
// 		}
// 		else
// 		{
// 			time = get_time();
// 			if (p->last_meal + p->data->time_to_die > time)
// 			{
// 				action_msg(*p, "died");
// 				ft_set_life(*p, *p->data);
// 				return (FAILURE);
// 			}
// 			usleep(100);
// 		}
// 	}
// 	return (0);
// }

// int	take_left_fork(t_philo *p)
// {
// 	size_t time;

// 	while (1)
// 	{
// 		if (pthread_mutex_lock(p->fork.left) ==  0)
// 		{
// 			action_msg(*p, "has taken a fork");
// 			return (SUCCESS);
// 		}
// 		else
// 		{
// 			time = get_time();
// 			if (p->last_meal + p->data->time_to_die > time)
// 			{
// 				action_msg(*p, "died");
// 				ft_set_life(*p, *p->data);
// 				return (FAILURE);
// 			}
// 			usleep(100);
// 		}
// 	}
// 	return (0);
// }

// int eating(t_philo *p)
// {
//     size_t time;

//     time = get_time();
//     pthread_mutex_lock(&p->m_meal);
//     p->last_meal = time;
//     pthread_mutex_unlock(&p->m_meal);

//     action_msg(*p, "is eating");
//     while (time + p->data->time_to_eat > get_time())
//     {
//         if (time + p->data->time_to_die < get_time())
//         {
//             ft_set_life(*p, *p->data);
//             return (FAILURE);
//         }
//         usleep(100);
//     }
//     // ft_usleep(p->data->time_to_eat);
//     pthread_mutex_unlock(p->fork.right);
//     pthread_mutex_unlock(p->fork.left);
//     pthread_mutex_lock(&p->m_nu_meal);
//     p->count_meal += 1;
//     pthread_mutex_unlock(&p->m_nu_meal);
//     return (SUCCESS);
// }

// int sleeping(t_philo *p)
// {
//     size_t l_meal;

//     pthread_mutex_lock(&p->m_meal);
//     l_meal = p->last_meal;
//     pthread_mutex_unlock(&p->m_meal);
//     action_msg(*p, "is sleeping");
//     while (l_meal + p->data->time_to_sleep > get_time())
//     {
//         if (l_meal + p->data->time_to_die < get_time())
//         {
//             ft_set_life(*p, *p->data);
//             return (FAILURE);
//         }
//         usleep(100);
//     }
//     return (SUCCESS);
// }