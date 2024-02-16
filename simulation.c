/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:13:49 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 15:13:59 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Starts the simulation by creating threads for each philosopher and a watcher thread (if there are more than 1 philosopher).
 * Sets the time of start for the simulation and initializes the last meal time for each philosopher.
 * 
 * @param data A pointer to the data structure containing information about the simulation.
 * @return 0 on success.
 */
int simulation_start(t_data *data)
{
    int i;

    data->time_of_start = ft_save_time() + (data->philos_total * 10);
    i = 0;
    while (i < data->philos_total)
    {
        pthread_create(&data->philos[i]->thread, NULL, &routine_philo, data->philos[i]);
        pthread_mutex_lock(&data->philos[i]->lock_philo);
        data->philos[i]->last_meal = data->time_of_start;
        pthread_mutex_unlock(&data->philos[i]->lock_philo);
        i++;
    }
    if (data->philos_total > 1)
    {
        pthread_create(&data->watcher_thread, NULL, &routine_watcher, data);
    }
    return 0;
}

/**
 * Ends the simulation by joining all philosopher threads and the watcher thread (if there are more than 1 philosopher).
 * 
 * @param data A pointer to the data structure containing information about the simulation.
 * @return 0 on success.
 */
int simulation_end(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philos_total)
    {
        pthread_join(data->philos[i]->thread, NULL);
        i++;
    }
    if (data->philos_total > 1)
    {
        pthread_join(data->watcher_thread, NULL);
    }
    return 0;
}
