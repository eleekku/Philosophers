/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:00:58 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/26 12:00:59 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0
# define ERRGENERIC "Argument must be over 0 and fit to an integer "
# define ERRGENERIC2 "and no more than 1000 philos\n"

typedef int					t_bool;
typedef struct s_philo		t_philo;
typedef struct s_maitred	t_maitred;

struct s_philo
{
	pthread_t			philo;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		mealtdata;
	pthread_mutex_t		mealsdata;
	int					index;
	int					meals_eaten;
	unsigned int		last_meal;
	t_maitred			*data;
};

struct s_maitred
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	start_time;
	int				meals;
	int				number_of_philos;
	pthread_t		maitre_d;
	t_bool			death;
	t_bool			finish;
	t_philo			**philo;
	pthread_mutex_t	print;
	pthread_mutex_t	finishdata;
	pthread_mutex_t	deathdata;
};

int				check_arguments(int argc, char **argv);
int				seat_philosophers(t_maitred *maitre_d);
int				assign_data(t_maitred *data, char **args);
unsigned int	get_time(void);
void			clean_table(t_maitred *maitre_d);
t_bool			check_stopper(t_philo *philo, int i);
void			*routines(void *arg);
unsigned int	oversee_helper(t_philo *philo, int i);
void			*oversee(void *maitre_d);
int				destroy_mutexes(t_maitred *maitre_d, int i, int mutexnumber);
#endif