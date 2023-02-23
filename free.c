#include "philo.h"

int destroy_mutex(t_philo *p, t_data data)
{
    int i;

    pthread_mutex_destroy(&data.m_life);
    pthread_mutex_destroy(&data.msg);
    i = 0;
    while (i < data.nu_philo)
    {
        pthread_mutex_destroy(&p[i].my_fork);
        pthread_mutex_destroy(&p[i].m_meal);
        pthread_mutex_destroy(&p[i].m_nu_meal);
        i++;
    }
    free(p);
    return (1);
}
