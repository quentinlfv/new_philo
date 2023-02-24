 #include "philo.h"

t_data init_data(char **argv, t_data data)
{
    data.life = 1;
    data.simbegin = get_time();
    data.nu_philo = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
    data.time_to_eat = ft_atoi(argv[3]);
    data.time_to_sleep = ft_atoi(argv[4]);
    pthread_mutex_init(&data.m_life, NULL);
    pthread_mutex_init(&data.msg, NULL);
     pthread_mutex_init(&data.m_must_eat, NULL);
    if (data.must_eat == 1)
        data.must_eat = ft_atoi(argv[5]);
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
        p[i].count_meal = 1;
        p[i].id = i + 1;
        p[i].data = data;
        p[i].last_meal = data->simbegin;
        pthread_mutex_init(&p[i].m_meal, NULL);
        pthread_mutex_init(&p[i].my_fork, NULL);
        pthread_mutex_init(&p[i].m_nu_meal, NULL);
        i++;
    }
    p = init_fork(p, data);
    return (p);
}

t_philo *init_fork(t_philo *p, t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nu_philo)
    {
        p[i].fork.right = &p[i].my_fork;
        if (p[i].id == data->nu_philo)
            p[i].fork.left = &p[0].my_fork;
        else
            p[i].fork.left = &p[i + 1].my_fork;
        i++;
    }
    return (p);
}

