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
	int	value;

	pthread_mutex_lock(&data->lock_end);
	value = data->death_flag;
	pthread_mutex_unlock(&data->lock_end);
	return (value);
}

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->lock_end);
	data->death_flag = 1;
	pthread_mutex_unlock(&data->lock_end);
}

