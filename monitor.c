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
	time_t curr_time;

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

int monitor_run(t_data *data)
{
	int	i;
	int	all_ate_enough;

	i = 0;
	all_ate_enough = 1;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		if (philo_died(data->philos[i]) == 0)
			return (0);
		if (data->num_of_meals != -1)
		{
			if (data->philos[i]->meals_eaten < data->num_of_meals)
				all_ate_enough = 0;
		}
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->num_of_meals != -1 && all_ate_enough == 1)
	{
		set_death_flag(data);
		return (0);
	}
	return (1);
}

void *monitor_routine(void *data_ptr)
{
	t_data *data;

	data = (t_data *)data_ptr;
	wait_for_all_threads(data->time_of_start);
	while (1)
	{
		if (monitor_run(data) == 0)
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
