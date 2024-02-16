/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:02 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:41:52 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_start(t_data *data)
{
	int			i;

	data->time_of_start = ft_save_time() + (data->philos_total * 10);
	i = 0;
	while (i < data->philos_total)
	{
		if (pthread_create(&data->philos[i]->thread, NULL,
				&routine_philo, data->philos[i]))
			ft_exit_error("Failed to create a philo thread.", data);
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		data->philos[i]->last_meal = data->time_of_start;
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->philos_total > 1)
	{
		if (pthread_create(&data->watcher_thread, NULL,
				&routine_watcher, data))
			ft_exit_error("Failed to create the watcher thread.", data);
	}
	return (0);
}

int	simulation_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_total)
	{
		if (pthread_join(data->philos[i]->thread, NULL))
			ft_exit_error("Failed to join a philo thread.", data);
		i++;
	}
	if (data->philos_total > 1)
	{
		if (pthread_join(data->watcher_thread, NULL))
			ft_exit_error("Failed to join the watcher thread.", data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	check_input(argc, argv);
	data = init_data(argc, argv);
	simulation_start(data);
	simulation_end(data);
	free_data(data);
	return (0);
}
