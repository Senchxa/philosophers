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


/**
 * Checks if a philosopher has died.
 * 
 * @param philo The philosopher to check.
 * @return 1 if the philosopher has died, 0 otherwise.
 */
int philo_died(t_philo *philo)
{
	uint64_t curr_time;

	if (get_eating_flag(philo) == 1)
		return 1;
	curr_time = ft_save_time();
	if ((curr_time - philo->last_meal) >= philo->data->time_to_die)
	{
		set_death_flag(philo->data);
		ft_print_status(philo, DIE);
		pthread_mutex_unlock(&philo->lock_philo);
		return 0;
	}
	return 1;
}

/**
 * @brief Watches for the end condition of the philosopher simulation.
 * 
 * This function checks if any philosopher has died or if all philosophers have finished eating the specified number of rounds.
 * If a philosopher has died, the function returns 0 to indicate the end condition has been met.
 * If all philosophers have finished eating the specified number of rounds, the function sets the death flag and returns 0.
 * Otherwise, the function returns 1 to indicate that the simulation is still ongoing.
 * 
 * @param data A pointer to the data structure containing information about the philosophers and simulation parameters.
 * @return int Returns 0 if the end condition has been met, 1 otherwise.
 */
int	watch_end(t_data *data)
{
	int	i;
	int	rounds_finished;

	i = 0;
	rounds_finished = 1;
	while (i < data->philos_total)
	{
		pthread_mutex_lock(&data->philos[i]->lock_philo);
		if (philo_died(data->philos[i]) == 0)
			return (0);
		if (data->rounds_total != -1)
		{
			if (data->philos[i]->rounds_eaten < data->rounds_total)
				rounds_finished = 0;
		}
		pthread_mutex_unlock(&data->philos[i]->lock_philo);
		i++;
	}
	if (data->rounds_total != -1 && rounds_finished == 1)
	{
		set_death_flag(data);
		return (0);
	}
	return (1);
}

/**
 * @brief Thread routine for watching the end condition.
 * 
 * This function is responsible for continuously checking the end condition
 * and returning if it is met. It also sleeps for 1 microsecond between checks.
 * 
 * @param data_ptr A pointer to the data structure containing the necessary information.
 * @return void* Always returns NULL.
 */
void *routine_watcher(void *data_ptr)
{
	t_data *data;

	data = (t_data *)data_ptr;
	synchronize_start(data->time_of_start);
	while (1)
	{
		if (watch_end(data) == 0)
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
