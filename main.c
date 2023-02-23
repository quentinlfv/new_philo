#include "philo.h"

int main(int argc, char **argv)
{
    t_philo *p;
    t_data  data;

    if (check_args(argc, &data) != 1)
        return (2);
    p = NULL;
    data = init_data(argv, data);
    p = init_philo(p, &data);
    launch_sim(p, data);
    destroy_mutex(p, data);
    return (0);
}