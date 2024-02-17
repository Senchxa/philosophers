/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:02 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/17 14:32:02 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_start(t_data *data)
{
	int		i;

	data->time_of_start = get_time() + (data->num_of_philos * 10);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philos[i]->thread, NULL, &routine_philo,
			data->philos[i]);
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		data->philos[i]->time_of_last_meal = data->time_of_start;
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->num_of_philos > 1)
		pthread_create(&data->monitor, NULL, &routine_watcher, data);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	if (data->num_of_philos > 1)
		pthread_join(data->monitor, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	check_input(ac, av);
	data = init_data(ac, av);
	simulation_start(data);
	free_data(data);
	return (0);
}
