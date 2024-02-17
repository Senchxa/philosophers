/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_watcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:47 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:35:48 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_died(t_philo *philo)
{
	uint64_t curr_time;

	/*if (get_eating_flag(philo) == 1)
		return 1;*/
	curr_time = get_time();
	if ((curr_time - philo->time_of_last_meal) >= philo->data->time_to_die)
	{
		set_death_flag(philo->data);
		ft_print_status(philo, DIE);
		pthread_mutex_unlock(&philo->lock_philo);
		return 0;
	}
	return 1;
}

int watch_end(t_data *data)
{
	int	i;
	int	rounds_finished;

	i = 0;
	rounds_finished = 1;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		if (philo_died(data->philos[i]) == 0)
			return (0);
		if (data->num_of_meals != -1)
		{
			if (data->philos[i]->meals_eaten < data->num_of_meals)
				rounds_finished = 0;
		}
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->num_of_meals != -1 && rounds_finished == 1)
	{
		set_death_flag(data);
		return (0);
	}
	return (1);
}

void *routine_watcher(void *data_ptr)
{
	t_data *data;

	data = (t_data *)data_ptr;
	wait_for_all_threads(data->time_of_start);
	while (1)
	{
		if (watch_end(data) == 0)
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
