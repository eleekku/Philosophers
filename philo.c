/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:00:23 by esalmela          #+#    #+#             */
/*   Updated: 2024/07/03 13:57:41 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	start_dining(t_maitred *maitre_d)
{
	int		i;

	maitre_d->start_time = get_time();
	i = 0;
	if (pthread_create(&maitre_d->maitre_d, NULL, &oversee, (t_maitred *)maitre_d) != 0)
	{
		printf("Error with creating maitre_d thread\n");
		return (-1);
	}
	while (i < maitre_d->number_of_philos)
	{
		if (pthread_create(&maitre_d->philo[i]->philo, NULL, &routines, (t_philo *)maitre_d->philo[i]) != 0)
		{
			pthread_join(maitre_d->maitre_d, NULL);
			printf("Error with creating philo thread");
			return (i);
		}
		i++;
	}	
	return (0);
}

int	create_threads(t_maitred *maitre_d)
{
	int	threads;
	int	i;

	i = -1;
	threads = start_dining(maitre_d);
	if (threads != 0)
	{	
		while (--threads >= 0)
			pthread_join(maitre_d->philo[threads]->philo, NULL);
		clean_table(maitre_d);
		return (1);
	}
	while (++i < maitre_d->number_of_philos)
		if (pthread_join(maitre_d->philo[i]->philo, NULL) != 0)
		{
			clean_table(maitre_d);
			return (1);
		}
	pthread_mutex_lock(&maitre_d->finishdata);
	maitre_d->finish = TRUE;
	pthread_mutex_unlock(&maitre_d->finishdata);
	return (0);
}

int init_philo(t_maitred *maitre_d, int i)
{
    maitre_d->philo[i] = malloc(sizeof(t_philo));
		if (!maitre_d->philo[i])
			{
                while (--i >= 0)
                    free (maitre_d->philo[i]);
                free(maitre_d->philo);
                return (1);
            }
	maitre_d->philo[i]->index = i + 1;
	maitre_d->philo[i]->data = maitre_d;
	if (pthread_mutex_init(&maitre_d->philo[i]->left_fork, NULL) != 0)
        return (destroy_mutexes(maitre_d, i, 0));
	if (pthread_mutex_init(&maitre_d->philo[i]->mealtdata, NULL) != 0)
        return (destroy_mutexes(maitre_d, i, 1));
    if (pthread_mutex_init(&maitre_d->philo[i]->mealsdata, NULL) != 0)
        return (destroy_mutexes(maitre_d, i, 2));
		if (i > 0)
			maitre_d->philo[i]->right_fork = &maitre_d->philo[i - 1]->left_fork;
	maitre_d->philo[i]->meals_eaten = 0;
	maitre_d->philo[i]->last_meal = 0;
	maitre_d->philo[i]->data = maitre_d;
    return (0);
}

int	seat_philosophers(t_maitred *maitre_d)
{
	int i;

	i = -1;

	maitre_d->philo = malloc(maitre_d->number_of_philos * sizeof(t_philo *));
	if (!maitre_d->philo)
		return (1);
	while (++i < maitre_d->number_of_philos)
	{
        if (init_philo(maitre_d, i) != 0)
            return (1);
	}
	maitre_d->philo[0]->right_fork = &maitre_d->philo[maitre_d->number_of_philos - 1]->left_fork;
    return (0);
}

int	main(int argc, char **argv)
{
	t_maitred	maitre_d;

	if (check_arguments(argc, argv) == 1)
		return (1);
	if (assign_data(&maitre_d, argv) != 0)
		return (1);
	if (seat_philosophers(&maitre_d) != 0)
		return (1);
	if (create_threads(&maitre_d) != 0)
		return (1);
	if (pthread_join(maitre_d.maitre_d, NULL) != 0)
	{
		clean_table(&maitre_d);
		return (1);
	}
	clean_table(&maitre_d);
	return (0);
}
