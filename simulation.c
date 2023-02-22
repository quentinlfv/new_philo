#include "philo.h"

void    *routine(void *arg)
{
    t_philo p;

    p = *(t_philo *)arg;

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
        pthread_mutex_lock()
        time = get_time();
        if (time - p[i].last_meal < data.simbegin)
        {
            data.life = 0;
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
}