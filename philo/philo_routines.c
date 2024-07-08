/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:01:52 by esalmela          #+#    #+#             */
/*   Updated: 2024/07/03 21:01:56 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	print_message(t_philo *philo, int i, unsigned int time)
{	
	unsigned int	timestamp;

	if (check_stopper(philo, 1) == TRUE || (philo->meals_eaten
			>= philo->data->meals && philo->data->meals != 0))
		return ;
	timestamp = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	if ((i == 1 || i == 2) && philo->data->death == FALSE)
		printf("%d %d has taken a fork\n", timestamp, philo->index);
	else if (i == 3 && philo->data->death == FALSE)
	{
		printf("%d %d is eating\n", time, philo->index);
		philo->last_meal = time;
	}
	else if (i == 4 && philo->data->death == FALSE)
		printf("%d %d is sleeping\n", timestamp, philo->index);
	else if (i == 5 && philo->data->death == FALSE)
		printf("%d %d is thinking\n", timestamp, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	return ;
}

static void	sleep_n_think(t_philo *p)
{
	pthread_mutex_lock(&p->mealsdata);
	p->meals_eaten++;
	pthread_mutex_unlock(&p->mealsdata);
	pthread_mutex_unlock(&p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	print_message(p, 4, 0);
	if (check_stopper(p, 1) == FALSE)
		usleep(p->data->time_to_sleep * 1000);
	print_message(p, 5, 0);
}

static void	eat(t_philo *p)
{
	unsigned int	time;

	while (p->data->meals == 0 || p->meals_eaten < p->data->meals)
	{
		if (check_stopper(p, 1) == TRUE)
			break ;
		pthread_mutex_lock(&p->left_fork);
		print_message(p, 1, 0);
		pthread_mutex_lock(p->right_fork);
		print_message(p, 2, 0);
		usleep(500);
		time = get_time() - p->data->start_time;
		print_message(p, 3, time);
		pthread_mutex_lock(&p->mealtdata);
		p->last_meal = time;
		pthread_mutex_unlock(&p->mealtdata);
		time = (p->data->time_to_eat -(get_time() - p->data->start_time
					- time));
		usleep(time * 1000);
		sleep_n_think(p);
	}
}

void	*routines(void *arg)
{
	t_philo	*current;

	current = arg;
	if (current->index % 2 == 0)
		eat(current);
	else
	{
		usleep((current->data->time_to_eat * 1000) - 10);
		eat(current);
	}
	return (0);
}
