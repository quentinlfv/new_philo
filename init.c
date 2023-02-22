#include "philo.h"

t_data init_data(int argc, char **argv, t_data data)
{
    struct timeval time;

    data.life = 1;
    data.simbegin = get_time();
    data.nu_philo = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    return (data);
}

t_philo *init_philo(t_philo *p, t_data *data)
{
    int i;

    i = 0;
    p = malloc(sizeof(t_philo) * data->nu_philo);
    if (!p)
    {
        perror("Failed to malloc\n");
        return (NULL);
    }
    i = 0;
    while (i < data->nu_philo)
    {
        p[i].id = i + 1;
        p[i].data = data;
        p[i].last_meal = data->simbegin;
        i++;
    }
}

size_t get_time(void)
{
    struct timeval get_time;
    size_t  time;

    gettimeofday(&time, NULL);
    time = get_time.tv_sec * 1000 + get_time.tv_usec / 1000;
    return (time);
}

