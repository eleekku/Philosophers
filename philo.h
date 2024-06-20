#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_philo
{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals;	
}	t_philo;
#endif
