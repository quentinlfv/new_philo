#include "philo.h"


void    eat(t_philo *p)
{
    pthread_mutex_lock(p->fork.right);
    action_msg(*p, "has taken a fork");
    pthread_mutex_lock(p->fork.left);
    action_msg(*p, "has taken a fork");
    action_msg(*p, "is eating");
    pthread_mutex_lock(&p->m_meal);
    p->last_meal = get_time();
    pthread_mutex_unlock(&p->m_meal);
    usleep(p->data->time_to_eat * 1000);
    pthread_mutex_unlock(p->fork.right);
    pthread_mutex_unlock(p->fork.left);
    pthread_mutex_lock(&p->m_nu_meal);
    p->count_meal += 1;
    pthread_mutex_unlock(&p->m_nu_meal);   
}


void    *routine(void *arg)
{
    t_philo *p;

    p = (t_philo *)arg;
    if (p->id % 2 == 0 || p->id == p->data->nu_philo)
    {
        action_msg(*p, "is thinking");
        usleep(p->data->time_to_eat * 1000);
    }
    while (1)
    {
        pthread_mutex_lock(&p->data->m_life);
        if (p->data->life == 0)
        {
            pthread_mutex_unlock(&p->data->m_life);
            break;
        }
        pthread_mutex_unlock(&p->data->m_life);
        eat(p);
        action_msg(*p, "is sleeping");
        usleep(p->data->time_to_sleep * 1000);
        action_msg(*p, "is thinking");
    }
    return (NULL);
}

int watch(t_philo *p, t_data data)
{
    size_t  time;
    size_t  meal;
    int     i;

    i = 0;
    while (1)
    {
        pthread_mutex_lock(&p[i].m_meal);
        meal = p[i].last_meal;
        pthread_mutex_unlock(&p[i].m_meal);
        time = get_time();
        if (!check_nu_meal(p, data.nu_philo))
        {
            pthread_mutex_lock(&data.m_life);
            p[i].data->life = 0;
            pthread_mutex_unlock(&data.m_life);
            break;
        }
        if (time - (meal + p[i].data->time_to_die) < data.simbegin)
        {
            action_msg(p[i], "died");
            pthread_mutex_lock(&data.m_life);
            p[i].data->life = 0;
            pthread_mutex_unlock(&data.m_life);
            break;
        }
        i = (i + 1) % data.nu_philo;
    }
    return (1);
}

int launch_sim(t_philo *p, t_data data)
{
    init_thread(p, data.nu_philo);
    watch(p, data);
    join_thread(p, data.nu_philo);
    return (1);
}