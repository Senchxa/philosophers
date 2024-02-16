/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:08 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 15:00:58 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc)
{
	if (argc < 5 || argc > 6)
		ft_exit_error("Please provide 5 or 6 arguments.", NULL);
}

void	check_format(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			ft_exit_error("Please provide digit arguments only.", NULL);
		i++;
	}
}

void	check_intmax(char *arg)
{
	int	num;

	num = ft_atoi(arg);
	if (num < 0)
		ft_exit_error("Please provide positive values only.", NULL);
}

void	check_values(char *arg, int i)
{
	if (i == 1)
	{
		if (ft_atoi(arg) < 1)
			ft_exit_error("At least 1 philosopher is required.", NULL);
	}
	else if (i == 5)
	{
		if (ft_atoi(arg) < 1)
			ft_exit_error("There must be at least 1 meal.", NULL);
	}
}

int	check_input(int argc, char **argv)
{
	int	i;

	check_args(argc);
	i = 1;
	while (argv[i] != NULL)
	{
		check_format(argv[i]);
		check_intmax(argv[i]);
		check_values(argv[i], i);
		i++;
	}
	return (0);
}
