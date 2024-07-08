/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:01:39 by esalmela          #+#    #+#             */
/*   Updated: 2024/07/03 21:01:43 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	long long	result;
	int			count;

	result = 0;
	count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '+' || *str == '-')
	{
		count++;
		str++;
		if (*str == ' ' || (*str >= 9 && *str <= 13) || (count > 1))
			return (0);
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > 2147483647)
			return (-1);
		str++;
	}
	return (result);
}

t_bool	ft_isdigit(char	*argument)
{
	int	i;

	i = -1;
	while (argument[++i])
	{
		if (argument[i] < 47 || argument[i] > 58)
			return (FALSE);
	}
	return (TRUE);
}

int	assign_data(t_maitred *data, char **args)
{
	data->number_of_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->death = FALSE;
	data->finish = FALSE;
	if (args[5])
		data->meals = ft_atoi(args[5]);
	else
		data->meals = 0;
	data->philo = NULL;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->deathdata, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		return (1);
	}
	if (pthread_mutex_init(&data->finishdata, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->deathdata);
		return (1);
	}
	return (0);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

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
		if ((i == 1 && ft_atoi(argv[1]) > 1000) || ft_atoi(argv[i]) < 1) 
		{
			write(2, ERRGENERIC, 46);
			write(2, ERRGENERIC2, 29);
			return (1);
		}
	}
	return (0);
}
