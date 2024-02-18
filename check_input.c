/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:08 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/18 15:13:00 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_values(char *arg, int i)
{
	if (i == 1)
	{
		if (integer_atoi(arg) < 1)
			ft_exit_error("At least 1 philosopher is required.", NULL);
	}
	else if (i == 5)
	{
		if (integer_atoi(arg) < 1)
			ft_exit_error("There must be at least 1 meal.", NULL);
	}
}

void	digit_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			ft_exit_error("Please provide positive digits only.", NULL);
		i++;
	}
}

int	integer_atoi(char *str)
{
	unsigned long long int	result;
	int						i;

	i = 0;
	result = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX)
		ft_exit_error("Provide a number smaller than INT_MAX.", NULL);
	return ((int)result);
}

int	check_input(int ac, char **av)
{
	int	i;
	int	nb;

	if (ac < 5 || ac > 6)
		ft_exit_error("Please provide 5 or 6 arguments.", NULL);
	i = 1;
	while (i < ac)
	{
		digit_only(av[i]);
		nb = integer_atoi(av[i]);
		check_values(av[i], i);
		i++;
	}
	return (0);
}
