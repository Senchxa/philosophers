/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:34:51 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:34:52 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Initializes the data structure with the provided arguments.
 * 
 * @param data The pointer to the data structure to be initialized.
 * @param ac The number of command-line arguments.
 * @param av The array of command-line arguments.
 */
void init_struct_data(t_data *data, int ac, char **av)
{
	// Initialize data members with command-line arguments
	data->philos_total = integer_atoi(av[1]);
	data->time_to_die = (uint64_t)integer_atoi(av[2]);
	data->time_to_eat = (uint64_t)integer_atoi(av[3]);
	data->time_to_sleep = (uint64_t)integer_atoi(av[4]);

	// Check if rounds_total argument is provided
	if (ac == 6)
		data->rounds_total = integer_atoi(av[5]);
	else
		data->rounds_total = -1;

	// Initialize death_flag to 0
	data->death_flag = 0;

	// Initialize lock_print mutex
	if (pthread_mutex_init(&data->lock_print, NULL) != 0)
		ft_exit_error("Failed to initiate the 'lock_print' mutex.", data);

	// Initialize lock_end mutex
	if (pthread_mutex_init(&data->lock_end, NULL) != 0)
		ft_exit_error("Failed to initiate the 'lock_end' mutex.", data);
}

/**
 * Initializes the array of philosopher structures.
 * 
 * @param data The pointer to the data structure.
 * @return The pointer to the array of philosopher structures.
 */
t_philo **init_struct_philos(t_data *data)
{
	t_philo **philos;
	int i;

	// Allocate memory for the array of philosopher structures
	philos = malloc(sizeof(t_philo) * data->philos_total);
	if (!philos)
		ft_exit_error("Failed to allocate memory for 'philos array'.", data);

	i = 0;
	while (i < data->philos_total)
	{
		// Allocate memory for each philosopher structure
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			ft_exit_error("Failed to allocate memory for 'philo'.", data);

		// Initialize lock_philo mutex
		if (pthread_mutex_init(&philos[i]->lock_philo, NULL) != 0)
			ft_exit_error("Failed to initiate a 'lock_philo' mutex.", data);

		// Initialize lock_eating mutex
		if (pthread_mutex_init(&philos[i]->lock_eating, NULL) != 0)
			ft_exit_error("Failed to initiate a 'lock_eating' mutex.", data);

		// Set data, id, rounds_eaten, and eating_flag for each philosopher
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->rounds_eaten = 0;
		philos[i]->eating_flag = 0;

		i++;
	}

	return philos;
}

/**
 * Places the forks for each philosopher.
 * 
 * @param data The pointer to the data structure.
 */
void place_forks(t_data *data)
{
	int i = 1;
	while (i < data->philos_total)
	{
		// Set the left and right forks for each philosopher
		data->philos[i]->fork_left = &data->locks_forks[i];
		data->philos[i]->fork_right = &data->locks_forks[i - 1];
		i++;
	}
	data->philos[0]->fork_left = &data->locks_forks[0];
	data->philos[0]->fork_right = &data->locks_forks[data->philos_total - 1];
}

/**
 * Initializes the forks.
 * 
 * @param data The pointer to the data structure.
 * @return The pointer to the array of mutexes representing the forks.
 */
pthread_mutex_t *init_forks(t_data *data)
{
	pthread_mutex_t *forks;
	int i;

	// Allocate memory for the array of mutexes representing the forks
	forks = malloc(sizeof(pthread_mutex_t) * data->philos_total);
	if (!forks)
		ft_exit_error("Malloc error", data);

	i = 0;
	while (i < data->philos_total)
	{
		// Initialize each fork mutex
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			ft_exit_error("Failed to initiate a 'fork' mutex.", data);

		i++;
	}

	return forks;
}

/**
 * Initializes the data structure and returns a pointer to it.
 * 
 * @param ac The number of command-line arguments.
 * @param av The array of command-line arguments.
 * @return The pointer to the initialized data structure.
 */
t_data *init_data(int ac, char **av)
{
	t_data *data;

	// Allocate memory for the data structure
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit_error("Malloc error", NULL);

	// Initialize the data structure
	init_struct_data(data, ac, av);
	data->philos = init_struct_philos(data);
	data->locks_forks = init_forks(data);
	place_forks(data);

	return data;
}
