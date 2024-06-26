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

void	assign_data(t_overseer *data, char **args)
{
	int i;

	i = 0;
	data->number_of_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		data->meals =  ft_atoi(args[5]);
	data->philo = malloc(ft_atoi(args[1]) * sizeof(t_philo));
	if (!data->philo)
		printf("malloc error occured\n");

}

int check_arguments(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 6 || argc > 7)
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

void	*get_time()
{
	struct timeval tv;
	long long milliseconds;
	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000; 
    printf("Milliseconds: %lld\n", milliseconds);
}

void	set_utensil(t_overseer *overseer)
{
	pthread_mutex_t *forks;
	int				i;

	i = 0;
	forks = malloc(overseer->number_of_philos * sizeof(pthread_mutex_t));
		if (!forks)
			printf("error\n");
	
}

void	start_feast(t_overseer *overseer)
{

}

int	main(int argc, char **argv)
{
	t_overseer	overseer;

	if (check_arguments(argc, argv) == 1)
		return (1);
	assign_data(&overseer, argv);
	set_utensils(&overseer);
	star_feast(&overseer);
	get_time();
	free(overseer.philo);
}
