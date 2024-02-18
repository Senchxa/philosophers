/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:40 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/18 15:26:38 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_philo *philo, time_t philo_sleep_time)
{
	ft_print_status(philo, SLEEP);
	ft_usleep(philo_sleep_time);
}

void	think_philo(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->lock_philo);
	time_to_think = philo->data->time_to_eat - philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->lock_philo);
	if (time_to_think < 0)
		time_to_think = 0;
	ft_print_status(philo, THINK);
	ft_usleep(time_to_think);
}

void	eat(t_philo *philo)
{
	forks_pickup(philo);
	ft_print_status(philo, EAT);
	pthread_mutex_lock(&philo->lock_philo);
	philo->time_of_last_meal = get_time();
	pthread_mutex_unlock(&philo->lock_philo);
	ft_usleep(philo->data->time_to_eat);
	if (!get_death_flag(philo->data))
	{
		pthread_mutex_lock(&philo->lock_philo);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->lock_philo);
	}
	forks_putdown(philo);
}

void	*lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork);
	ft_print_status(philo, FORK_EQUIP);
	ft_usleep(philo->data->time_to_die);
	ft_print_status(philo, DIED);
	pthread_mutex_unlock(&philo->first_fork);
	return (NULL);
}

void	*routine_philo(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	wait_for_all_threads(philo->data->time_of_start);
	if (philo->data->num_of_philos == 1)
		return (lonely_philo(philo));
	while (get_death_flag(philo->data) != 1)
	{
		eat(philo);
		sleep_philo(philo, philo->data->time_to_sleep);
		think_philo(philo);
	}
	return (NULL);
}
