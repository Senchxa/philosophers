/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:36:10 by dnoll             #+#    #+#             */
/*   Updated: 2024/02/18 15:33:46 by dnoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DIED			"died"
# define THINK			"is thinking"
# define FORK_EQUIP		"has taken a fork"
# define SLEEP			"is sleeping"
# define EAT			"is eating"

# define GREEN			"\033[0;32m"
# define RED			"\033[0;31m"
# define RESET			"\033[0m"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h> 
# include <sys/time.h> 
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	pthread_mutex_t	lock_philo;
	time_t			time_of_last_meal;
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
	time_t			time_of_start;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
}			t_data;

// main.c
int				simulation_start(t_data *data);

// check_input.c
int				check_input(int ac, char **av);
int				integer_atoi(char *str);
void			digit_only(char *str);
void			check_values(char *arg, int i);

// death_flag.c
int				get_death_flag(t_data *data);
void			set_death_flag(t_data *data);

// exit.c
int				ft_exit_error(char *error, t_data *data);
int				free_data(t_data *data);

// fork_utils.c
void			forks_pickup(t_philo *philo);
void			forks_putdown(t_philo *philo);

// init.c
t_data			*init_data(int ac, char **av);
void			init_struct_data(t_data *data, int ac, char **av);
t_philo			**init_struct_philos(t_data *data);
pthread_mutex_t	*init_forks(t_data *data);
void			assign_forks(t_data *data);

// monitor.c
void			*monitor_routine(void *data_ptr);
int				monitor_run(t_data *data);
int				philo_died(t_philo *philo);

// routine_philo.c
void			*routine_philo(void *philo_ptr);
void			*lonely_philo(t_philo *philo);
void			eat(t_philo *philo);
void			sleep_philo(t_philo *philo, int64_t philo_sleep_time);
void			think_philo(t_philo *philo);

// utils.c
void			wait_for_all_threads(time_t time_of_start);
time_t			get_time(void);
int				ft_usleep(time_t time);
int				ft_print_status(t_philo	*philo, char *status);
int				ft_strcmpr(const char *s1, const char *s2);

#endif
