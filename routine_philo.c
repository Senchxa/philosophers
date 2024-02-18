/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:40 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:35:41 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_philo *philo, int64_t philo_sleep_time)
{
	ft_print_status(philo, SLEEP);
	ft_usleep(philo_sleep_time);
}

void	think_philo(t_philo *philo)
{
	int64_t	think_time;

	pthread_mutex_lock(&philo->lock_philo);
	if (philo->data->num_of_philos % 2 == 0)
		think_time = philo->data->time_to_eat - philo->data->time_to_sleep;
	else
		think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->lock_philo);
	if (think_time < 0)
		think_time = 0;
	ft_print_status(philo, THINK);
	ft_usleep(think_time);
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
	pthread_mutex_lock(philo->first_fork);
	ft_print_status(philo, FORK_EQUIP);
	ft_usleep(philo->data->time_to_die);
	ft_print_status(philo, DIE);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}

void	*routine_philo(void *philo_ptr)
{	
	t_philo	*philo;
	philo = (t_philo *)philo_ptr;
	wait_for_all_threads(philo->data->time_of_start);
	if (philo->data->num_of_philos == 1)
		return (lonely_philo(philo));
	if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat);
	while (get_death_flag(philo->data) != 1)
	{
		eat(philo);
		sleep_philo(philo, philo->data->time_to_sleep);
		think_philo(philo);
	}
	return (NULL);
}
