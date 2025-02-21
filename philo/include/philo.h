/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:29:30 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 17:09:12 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//====<[ Include guards: ]>=====================================================
#ifndef PHILO_H
# define PHILO_H

//====<[ Headers: ]>============================================================
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

//====<[ Macros: ]>=============================================================

//====<[ Macros: menu ]>==========================
# define PROGRAM_NAME "philo"
# define ARG_1 "[number_of_philosophers]"
# define ARG_2 "[time_to_die]"
# define ARG_3 "[time_to_eat]"
# define ARG_4 "[time_to_sleep]"
# define ARG_5 "[number_of_times_each_philosopher_must_eat]"
# define DEFINITION " Simulation of dinning philosofer problem."
# define ARG_1_USAGE "It should be at least one philosopher."
# define ARG_USAGE "It should be >= 0."
# define ARG_5_USAGE "(OPTIONAL), It should be > 0."
# define FAILURE_REASON "If at least one argument is invalid,"
# define FAILURE_ACTION "The program will fail and show up a usage menu."
# define SUCCESS_ACTION  "On success, The simualtion starts,"
# define SUCCESS_REASON "Until a philo die or reash max_meals."

//====<[ Macros: actions ]>=======================
# define EAT "%llu %d is eating\n"
# define THINK "%llu %d is thinking\n"
# define SLEEP "%llu %d is sleeping\n"
# define DIE "%llu %d died\n"
# define TAKE_FORK "%llu %d has taken a fork\n"

//====<[ Macros: exit status ]>===================
# define FAILURE 1
# define SUCCESS 0

//====<[ Macros: logical values ]>================
# define FALSE 0
# define TRUE 1 

//====<[ Macros: Fork states ]>===================
# define TAKEN 0
# define AVAILABLE 1

//====<[ Types: ]>==============================================================
typedef unsigned long long int	t_ullint;

//====<[ Structs: ]>============================================================

//====<[ Struct: s_fork ]>========================
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				status;
}					t_fork;

//====<[ Struct: t_args ]>========================
typedef struct s_args
{
	int				philos_nbr;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				max_meals;
}					t_args;

//====<[ Struct: t_print ]>=======================
typedef struct s_print
{
	pthread_mutex_t	print_mutex;
	int				access;
}				t_print;

//====<[ Struct: t_meal ]>========================
typedef struct s_meal
{
	pthread_mutex_t	meal_mutex;
	int				meals;
}					t_meal;

//====<[ Struct: t_philo ]>=======================
typedef struct s_philo
{
	int				id;
	t_args			*time;
	int				(*actions[3])(struct s_philo *);
	t_print			*print;
	t_meal			*meal;
	t_ullint		last_meal;
	pthread_t		thread;
	t_fork			*right;
	t_fork			*left;
}					t_philo;

//====<[ Struct: t_init ]>========================
typedef struct s_init
{
	t_args				*args;
	t_philo				*phs;
	t_fork				*forks;
}					t_init;

//====<[ Functions: prototypes ]>===============================================

//====<[ Function: philo_init ]>==================
t_init		*dining_philosofers_init(t_init *init, int ac, char **av);
t_args		*get_args(int ac, char **av);
t_philo		*take_seats_around_table(t_init *init);
t_fork		*put_forks_on_table(t_init *init);
int			start_simulation(t_init *init);

//====<[ Function: actions ]>=====================
void		*live_cycle(void *args);
int			start_eating(t_philo *p);
int			start_thinking(t_philo *p);
int			start_sleeping(t_philo *p);
int			meals_monitor(t_philo *p);

//====<[ Function: philo_utils ]>=================
int			take_fork(t_philo *p, t_fork *fork);
int			put_forks(t_philo *p);

//====<[ Function: utils ]>=======================
int			ft_atoi(char *s);
t_ullint	get_current_time(void);
int			my_usleep(t_philo *p, t_ullint start, t_ullint duration);
int			ft_strcmp(char *s1, char *s2);
int			clear_table(t_init *init);
void		display_usage_menu(void);
int			print_action(t_philo *phs, char *action);

#endif
//==============================================================================
