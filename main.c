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

int	main(int ac, char **av)
{
	t_data *data;

	data = NULL;
	check_input(ac, av);
	data = init_data(ac, av);
	simulation_start(data);
	simulation_end(data);
	free_data(data);
	return (0);
}
