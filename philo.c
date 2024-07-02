/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:00:23 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/26 12:00:25 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int ft_atoi(const char *str)
{
    int sign;
    int result;
    int count;

    sign = 1;
    result = 0;
    count = 0;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    while (*str == '+' || *str == '-')
    {
        count++;
        if (*str == '-')
            sign *= -1;
        str++;
        if (*str == ' ' || (*str >= 9 && *str <= 13) || (count > 1))
            return (0);
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

t_bool	ft_isdigit(char	*argument)
{
	int i;

	i = -1;
	while (argument[++i])
	{
		if (argument[i] < 47 || argument[i] > 58)
			return (FALSE);
	}
	return (TRUE);
}

void	assign_data(t_maitred *data, char **args)
{
	int i;

	i = 0;
	data->number_of_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->death = FALSE;
	data->finish = FALSE;
	if (args[5])
		data->meals =  ft_atoi(args[5]);
	else 
		data->meals = 0;
	data->philo = NULL;
	pthread_mutex_init(&data->print, NULL);
}

int check_arguments(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	while (++i < argc)
	{
		if (ft_isdigit(argv[i]) == FALSE)
		{	
			write(2, "Argument must be numeric type\n", 30);
			return (1);
		}
		if (i == 1)
		{
			if (ft_atoi(argv[i]) < 1)
				write(2, "Must be at least one philosopher\n", 34);
		}
	}
	return (0);
}

unsigned int	get_time(void)
{
	struct timeval tv;

	unsigned int milliseconds;
	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000; 
	return (milliseconds);
}

void	seat_philosophers(t_maitred *maitre_d)
{
	t_philo	**philo;
	int i;

	i = -1;
	maitre_d->philo = malloc(maitre_d->number_of_philos * sizeof(t_philo *));
		if (!maitre_d->philo)
			printf("error\n");
	while (++i < maitre_d->number_of_philos)
	{
		maitre_d->philo[i] = malloc(sizeof(t_philo));
			if (!maitre_d->philo[i])
				printf("error\n");
		maitre_d->philo[i]->index = i + 1;
		maitre_d->philo[i]->data = maitre_d;
		pthread_mutex_init(&maitre_d->philo[i]->left_fork, NULL);
		if (i > 0)
		maitre_d->philo[i]->right_fork = &maitre_d->philo[i - 1]->left_fork;
		maitre_d->philo[i]->meals_eaten = 0;
		maitre_d->philo[i]->last_meal = 0;
		maitre_d->philo[i]->data = maitre_d;
	}
	maitre_d->philo[0]->right_fork = &maitre_d->philo[maitre_d->number_of_philos - 1]->left_fork;
}
		 
void	clean_table(t_maitred *maitre_d)
{
	int i;

	i = 0;
	while (i < maitre_d->number_of_philos)
	{
		pthread_mutex_destroy(&maitre_d->philo[i]->left_fork);
		free (maitre_d->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&maitre_d->print);
	free (maitre_d->philo);
}

void	print_message(t_philo *philo, int i, unsigned int time)
{	
	unsigned int	timestamp;

	if (philo->data->death == TRUE)
		return;
	pthread_mutex_lock(&philo->data->print);
	timestamp = get_time() - philo->data->start_time;
	if (i == 1 && philo->data->death == FALSE)
		printf("%d philo %d has taken a left fork\n", timestamp, philo->index);
	else if (i == 2 && philo->data->death == FALSE) 
		printf("%d philo %d has taken a right fork\n", timestamp, philo->index);
	else if (i == 3 && philo->data->death == FALSE)
	{
		printf("%d philo %d is eating\n", time, philo->index);
		philo->last_meal = time;
	}
	else if (i == 4 && philo->data->death == FALSE)
		printf("%d philo %d is sleeping\n", timestamp, philo->index);
	else if (i == 5 && philo->data->death == FALSE)
		printf("%d philo %d is thinking\n", timestamp, philo->index);
	pthread_mutex_unlock(&philo->data->print);
	return;	
}

void	*eat(void *arg)
{
	t_philo	*current;
	unsigned int	time;

	current = arg;
	while (current->data->death == FALSE && (current->data->meals == 0 || current->meals_eaten < current->data->meals))
	{
	pthread_mutex_lock(&current->left_fork);
	print_message(current, 1, 0);
	//if (current->data->death == TRUE)
		//pthread_mutex_unlock(&current->left_fork);
	//if (current->data->death == TRUE)
		//pthread_mutex_unlock(current->right_fork);
	pthread_mutex_lock(current->right_fork);
	print_message(current, 2, 0);
	usleep(500);
	time = get_time() - current->data->start_time;
	print_message(current, 3, time); 
	current->last_meal = time;
	time = (current->data->time_to_eat -(get_time() - current->data->start_time - time));
	usleep(time * 1000);
	current->meals_eaten++;
	pthread_mutex_unlock(&current->left_fork);
	pthread_mutex_unlock(current->right_fork);
	print_message(current, 4, 0);
	time = (current->data->time_to_sleep -(get_time() - current->data->start_time - time));
	if (current->data->death == FALSE)
		usleep(current->data->time_to_sleep * 1000);
	print_message(current, 5, 0);
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
		usleep(400);
		eat(current);
	}		
}

void	*oversee(void *maitre_d)
{
	int i;
	t_maitred *m;
	unsigned int	timestamp;

	m = maitre_d;
	i = 0;
	while (m->finish == FALSE)
	{
		if (i == m->number_of_philos)
			i = 0;
		timestamp = get_time() - m->start_time - m->philo[i]->last_meal;
		if (timestamp > m->time_to_die && (m->philo[i]->meals_eaten < m->meals || m->meals == 0))
		{
			pthread_mutex_lock(&m->print);
			m->death = TRUE;
			timestamp = get_time() - m->start_time - m->philo[i]->last_meal;
			printf("%d philo %d died\n", timestamp, m->philo[i]->index);
			pthread_mutex_unlock(&m->print);
			i = -1;
			while (++i < m->number_of_philos)
				pthread_mutex_unlock(&m->philo[i]->left_fork);
			break ;
		}
		i++;
	}
}

void	start_dining(t_maitred *maitre_d)
{
	int		i;

	maitre_d->start_time = get_time();
	i = 0;
	pthread_create(&maitre_d->maitre_d, NULL, &oversee, (t_maitred *)maitre_d);
	while (i < maitre_d->number_of_philos)
	{
		pthread_create(&maitre_d->philo[i]->philo, NULL, &routines, (t_philo *)maitre_d->philo[i]);
		i++;
	}	
}

int	main(int argc, char **argv)
{
	t_maitred	maitre_d;
	int			i;

	i = -1;
	if (check_arguments(argc, argv) == 1)
		return (1);
	assign_data(&maitre_d, argv);
	seat_philosophers(&maitre_d);
	start_dining(&maitre_d);
	while (++i < maitre_d.number_of_philos)
	pthread_join(maitre_d.philo[i]->philo, NULL);
	maitre_d.finish = TRUE;
	pthread_join(maitre_d.maitre_d, NULL);
	clean_table(&maitre_d);
}
