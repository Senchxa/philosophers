/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:30 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:34:31 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_pickup(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->first_fork);
	else
		pthread_mutex_lock(philo->second_fork);
	ft_print_status(philo, FORK_EQUIP);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->second_fork);
	else
		pthread_mutex_lock(philo->first_fork);

}

void	forks_putdown(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_unlock(philo->first_fork);
	else
		pthread_mutex_unlock(philo->second_fork);
	if (philo->id % 2 == 1)
		pthread_mutex_unlock(philo->second_fork);
	else
		pthread_mutex_unlock(philo->first_fork);
}
