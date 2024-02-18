/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:51 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/17 13:52:04 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_struct_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!philos)
		ft_exit_error("Failed to allocate memory for 'philos array'.", data);
	i = 0;
	while (i < data->num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			ft_exit_error("Failed to allocate memory for 'philo'.", data);
		pthread_mutex_init(&philos[i]->lock_philo, NULL);
		pthread_mutex_init(&philos[i]->lock_eating, NULL);
		philos[i]->data = data;
		philos[i]->id = i + 1;
		philos[i]->meals_eaten = 0;
		i++;
	}
	return (philos);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->num_of_philos)
	{
		data->philos[i]->first_fork = &data->forks_array[i];
		data->philos[i]->second_fork = &data->forks_array[i - 1];
		i++;
	}
	data->philos[0]->first_fork = &data->forks_array[0];
	data->philos[0]->second_fork = &data->forks_array[data->num_of_philos - 1];
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!forks)
		ft_exit_error("Malloc error", data);
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit_error("Malloc error", NULL);
	data->num_of_philos = integer_atoi(av[1]);
	data->time_to_die = (uint64_t)integer_atoi(av[2]);
	data->time_to_eat = (uint64_t)integer_atoi(av[3]);
	data->time_to_sleep = (uint64_t)integer_atoi(av[4]);
	data->num_of_meals = -1;
	if (ac == 6)
		data->num_of_meals = integer_atoi(av[5]);
	data->death_flag = 0;
	pthread_mutex_init(&data->lock_print, NULL);
	pthread_mutex_init(&data->lock_end, NULL);
	data->philos = init_struct_philos(data);
	data->forks_array = init_forks(data);
	assign_forks(data);
	return (data);
}
