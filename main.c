/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:35:02 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:41:52 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @file main.c
 * @brief The main function of the program.
 *
 * This file contains the main function of the program. 
 	It serves as the entry point
 * of the program, initializing the data, checking the input, starting the simulation,
 * and freeing the allocated memory.
 */

int main(int argc, char **argv)
{
	t_data *data;

	data = NULL;
	check_input(argc, argv);
	data = init_data(argc, argv);
	simulation_start(data);
	simulation_end(data);
	free_data(data);
	return 0;
}
