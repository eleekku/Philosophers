/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:05 by esalmela          #+#    #+#             */
/*   Updated: 2024/07/03 21:05:05 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval tv;

	unsigned int milliseconds;
	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000; 
	return (milliseconds);
}

void	clean_table(t_maitred *maitre_d)
{
	int i;

    i = 0;
	while (i < maitre_d->number_of_philos)
	{
		pthread_mutex_destroy(&maitre_d->philo[i]->left_fork);
		pthread_mutex_destroy(&maitre_d->philo[i]->mealtdata);
		pthread_mutex_destroy(&maitre_d->philo[i]->mealsdata);
		free (maitre_d->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&maitre_d->print);
	pthread_mutex_destroy(&maitre_d->deathdata);
	pthread_mutex_destroy(&maitre_d->finishdata);
	free (maitre_d->philo);
}

t_bool check_stopper(t_philo *philo, int i)
{
	t_bool status;
    
	status = FALSE;
    if (i == 1)
    {
	pthread_mutex_lock(&philo->data->deathdata);
	if (philo->data->death == TRUE)
		status = TRUE;
	pthread_mutex_unlock(&philo->data->deathdata);
    }
    if (i == 2)
    {
    pthread_mutex_lock(&philo->data->finishdata);
    if (philo->data->finish == TRUE)
        status = TRUE;
    pthread_mutex_unlock(&philo->data->finishdata);
    }
	return (status);	
}

unsigned int	oversee_helper(t_philo *philo, int i)
{
	unsigned int	value;

	value = 0;
	if (i == 1)
	{
		pthread_mutex_lock(&philo->mealtdata);
		value = get_time() - philo->data->start_time - philo->last_meal;
		pthread_mutex_unlock(&philo->mealtdata);
	}
	if (i == 2)
	{
		pthread_mutex_lock(&philo->mealsdata);
		value = philo->meals_eaten;
		pthread_mutex_unlock(&philo->mealsdata);
	}
	if (i == 3)
	{
		pthread_mutex_lock(&philo->data->deathdata);
		philo->data->death = TRUE;
		pthread_mutex_unlock(&philo->data->deathdata);
	}
	return (value);
}

int destroy_mutexes(t_maitred *maitre_d, int i, int mutexnumber)
{
	if (mutexnumber == 1)
	    pthread_mutex_destroy(&maitre_d->philo[i]->left_fork);
    if (mutexnumber == 2)
    {
	    pthread_mutex_destroy(&maitre_d->philo[i]->left_fork);
	    pthread_mutex_destroy(&maitre_d->philo[i]->mealtdata);
    }
    i--;
    while (i >= 0)
	{
		pthread_mutex_destroy(&maitre_d->philo[i]->left_fork);
		pthread_mutex_destroy(&maitre_d->philo[i]->mealtdata);
		pthread_mutex_destroy(&maitre_d->philo[i]->mealsdata);
	}
	return (1);
}
