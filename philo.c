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

void	assign_data(t_philo *data, char **args)
{
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		data->meals =  ft_atoi(args[5]);
}

int check_arguments(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 6 || argc > 7)
	{
		write(1, "Invalid number of arguments\n", 28);
		return (1);
	}
	while (++i < argc)
		if (ft_isdigit(argv[i]) == FALSE)
	{	
		write(1, "Argument must be numeric type\n", 30);
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (check_arguments(argc, argv) == 1)
		return (1);
	assign_data(&data, argv);
}
