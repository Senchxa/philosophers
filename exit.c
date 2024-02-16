/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:37 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:34:38 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_exit_error(char *error, t_data *data)
{
	printf("Error\n%s\n", error);
	if (data != NULL)
		free_data(data);
	exit (1);
}

int	free_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->philos_total)
		{
			pthread_mutex_destroy(&data->locks_forks[i]);
			pthread_mutex_destroy(&data->philos[i]->lock_eating);
			pthread_mutex_destroy(&data->philos[i]->lock_philo);
			i++;
		}
	}
	pthread_mutex_destroy(&data->lock_end);
	pthread_mutex_destroy(&data->lock_print);
	return (0);
}

int	free_data(t_data *data)
{
	int	i;

	if (!data)
		return (0);
	if (data)
		free_mutexes(data);
	if (data->locks_forks)
		free(data->locks_forks);
	i = 0;
	if (data->philos)
	{
		while (i < data->philos_total)
		{
			if (data->philos[i])
				free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	if (data)
		free(data);
	return (0);
}
