/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:36:10 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/16 14:36:13 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DIE			"died"
# define THINK			"is thinking"
# define FORK_EQUIP		"has taken a fork"
# define EAT			"is eating"
# define SLEEP			"is sleeping"

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h> // for uint64_t
# include <pthread.h> // for threads
# include <unistd.h> // for usleep
# include <sys/time.h> // for gettimeofday
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	lock_philo;
	pthread_mutex_t	lock_eating;
	uint64_t		time_of_last_meal;
}			t_philo;

typedef struct s_data
{
	struct s_philo	**philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks_array;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_end;
	int				num_of_meals;
	int				num_of_philos;
	int				death_flag;
	uint64_t		time_of_start;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
}			t_data;

// check_input.c
int				check_input(int ac, char **av);
int	integer_atoi(char *str);
void			digit_only(char *str);
void			check_values(char *arg, int i);

// init.c
t_data			*init_data(int ac, char **av);
void			init_struct_data(t_data *data, int ac, char **av);
t_philo			**init_struct_philos(t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
void			assign_forks(t_data *data);

// simulation.c
int				simulation_start(t_data *data);

void			*routine_philo(void *philo_ptr);
void			*lonely_philo(t_philo *philo);
void			eat(t_philo *philo);
void			forks_pickup(t_philo *philo);
void			forks_putdown(t_philo *philo);
void			sleep_philo(t_philo *philo, int64_t philo_sleep_time);
void			think_philo(t_philo *philo);


void			*routine_watcher(void *data_ptr);
int				watch_end(t_data *data);
int				philo_died(t_philo *philo);

// getters_setters.c
int				get_death_flag(t_data *data);
void			set_death_flag(t_data *data);


// utils.c
uint64_t		get_time(void);
int				ft_usleep(uint64_t time);
void			wait_for_all_threads(uint64_t time_of_start);
int				ft_print_status(t_philo	*philo, char *status);

// exit.c
int				ft_exit_error(char *error, t_data *data);
int				free_data(t_data *data);

#endif