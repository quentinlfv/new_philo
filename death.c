#include "philo.h"

void	ft_set_life(t_philo p, t_data *data)
{
	pthread_mutex_lock(&data->m_life);
	p.data->life = 0;
    pthread_mutex_unlock(&data->m_life);	
}

bool    is_philo_dead(t_philo *p)
{
    bool    death;

    death = false;
    pthread_mutex_lock(&p->data->m_life);
    if (p->data->life == 0)
        death = true;
    pthread_mutex_unlock(&p->data->m_life);
    return (death);
}

bool    philo_is_dead(t_philo *p)
{
    size_t time;

    time = get_time();
    if (time - p->last_meal > p->data->time_to_die)
    {
        ft_set_life(*p, p->data);
        action_msg(*p, "died");
        pthread_mutex_lock(&p->m_meal);
        return (true);
    }
    return (false);
}

bool	check_if_philo_dead(t_data *data)
{
    bool    num_meals;
	int		i;

    num_meals = true;
	i = 0;
    while (i < data->nu_philo)
    {
	    pthread_mutex_lock(&data->philo[i]->m_meal);
        if (philo_is_dead(data->philo[i]) == true)
        return (true);
	    if (data->philo[i]->count_meal < data->must_eat)
            num_meals = false;
        pthread_mutex_unlock(&data->philo[i]->m_meal);
        i++;
    }
    if (data->must_eat != -1 && num_meals == true)
    {
        ft_set_life(*data->philo[0], data);
        return (true);
    }
	return (false);
}

void    *check_death_conditions(void *arg)
{
    t_data  *data;

    data = (t_data *)arg;
    if (data->must_eat == 0)
        return(NULL);
    while (1)
    {
        if (check_if_philo_dead(data) == true)
            return (NULL);
        usleep(100);
    }
    return (NULL);
}