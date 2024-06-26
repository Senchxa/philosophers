/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:52 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/18 15:21:48 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

int	ft_usleep(time_t time)
{
	time_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(1);
	return (0);
}

int	ft_print_status(t_philo	*philo, char *status)
{
	time_t	curr_time;

	pthread_mutex_lock(&philo->data->lock_print);
	if (get_death_flag(philo->data) == 1 && status[0] != 'd')
	{
		pthread_mutex_unlock(&philo->data->lock_print);
		return (0);
	}
	curr_time = get_time() - philo->data->time_of_start;
	if (ft_strcmpr(status, "died") == 0)
		printf(RED"%lu\t\t%d\t\t%s\n"RESET, curr_time, philo->id, status);
	else if (ft_strcmpr(status, "is eating") == 0)
		printf(GREEN"%lu\t\t%d\t\t%s\n"RESET, curr_time, philo->id, status);
	else
		printf("%lu\t\t%d\t\t%s\n", curr_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->lock_print);
	return (0);
}

void	wait_for_all_threads(time_t time_of_start)
{
	while (get_time() < time_of_start)
		continue ;
}

int	ft_strcmpr(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (1);
	return (0);
}
