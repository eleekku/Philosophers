/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oversee.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:01:19 by esalmela          #+#    #+#             */
/*   Updated: 2024/07/03 21:01:20 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	declare_death(t_maitred *m, int i)
{
	unsigned int	timestamp;

	pthread_mutex_lock(&m->print);
	oversee_helper(m->philo[i], 3);
	timestamp = get_time() - m->start_time;
	printf("%d %d died\n", timestamp, m->philo[i]->index);
	pthread_mutex_unlock(&m->print);
	if (m->number_of_philos == 1)
		pthread_mutex_unlock(&m->philo[i]->left_fork);
}

void	*oversee(void *maitre_d)
{
	int				i;
	int				meals_eaten;
	t_maitred		*m;
	unsigned int	timestamp;

	m = maitre_d;
	i = 0;
	while (1)
	{	
		if (i == m->number_of_philos)
			i = 0;
		if (check_stopper(m->philo[i], 2) == TRUE)
			break ;
		timestamp = oversee_helper(m->philo[i], 1);
		meals_eaten = oversee_helper(m->philo[i], 2);
		if (timestamp > m->time_to_die && (meals_eaten < m->meals
				|| m->meals == 0))
		{
			declare_death(m, i);
			break ;
		}
		i++;
	}
	return (0);
}
