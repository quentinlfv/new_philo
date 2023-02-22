#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
    int life;
    int nu_philo;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    size_t  simbegin;
}t_data;

typedef struct s_philo
{
    int id;
    size_t      last_meal;
    pthread_t   philo;
    t_data      *data;
}t_philo;

/* init.c */
t_data init_data(int argc, char **argv, t_data data);
size_t get_time(void);

/* simulation.c */

/* thread.c */
int init_thread(t_philo *p, size_t nu);
int join_thread(t_philo *p, size_t nu);

/* utils.c */
size_t	ft_atoi(const char *nptr);



#endif