#include "philo.h"

int check_nu_meal(t_philo *p, int nu)
{
    int     i;
    size_t  count;

    i = 0;
    if (p[i].data->must_eat == 0)
        return (1);
    while (i < nu)
    {
        pthread_mutex_lock(&p[i].m_nu_meal);
        count = p[i].count_meal;
        pthread_mutex_unlock(&p[i].m_nu_meal);
        if ((int)count - (int)p[i].data->must_eat <= 0)
            break;
        if (p[i].id == nu)
            return (0);
       i++;
    }
    return (1);
}

int check_args(int argc, t_data *data)
{
    if (argc == 5)
        data->must_eat = 0;
    else if (argc == 6)
        data->must_eat = 1;
    else if (argc > 6)
    {
        perror("too much args pipis");
        return (0);
    }
    return (1);
}
