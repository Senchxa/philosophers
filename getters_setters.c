/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:44 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:34:46 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_death_flag(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->lock_end);
	res = data->death_flag;
	pthread_mutex_unlock(&data->lock_end);
	return (res);
}

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->lock_end);
	data->death_flag = 1;
	pthread_mutex_unlock(&data->lock_end);
}

int	get_eating_flag(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->lock_eating);
	res = philo->eating_flag;
	pthread_mutex_unlock(&philo->lock_eating);
	return (res);
}

void	set_eating_flag(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->lock_eating);
	philo->data->death_flag = flag;
	pthread_mutex_unlock(&philo->lock_eating);
}
