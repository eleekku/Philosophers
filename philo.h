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

typedef int	t_bool;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	left_fork;
	pthread_mutex_t right_fork;
	struct s_philo  *next;
}	t_philo;

typedef struct s_overseer
{
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_philos;
	int		meals;
	t_philo	*philo;	
}	t_overseer;
#endif
