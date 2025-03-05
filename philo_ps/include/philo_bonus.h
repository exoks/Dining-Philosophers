/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:29:30 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 17:02:13 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//====<[ Include guards: ]>=====================================================
#ifndef __PHILO_H__
# define __PHILO_H__

//====<[ Headers: ]>============================================================
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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
# define DIED 0

//====<[ Macros: simaphores ]>====================
# define SEM_PRINTER "sem_print"
# define SEM_MEALS "sem_meals"
# define SEM_FORKS "sem_forks"

//====<[ Types: ]>==============================================================
typedef unsigned long long int	t_ullint;

//====<[ Structs: ]>============================================================

//====<[ Struct: s_fork ]>========================
typedef struct t_args
{
	int				philos_nbr;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				max_meals;
}					t_args;

//====<[ Struct: t_general ]>=====================
typedef struct s_general
{
	sem_t			*printer;
	sem_t			*meals;
}					t_general;

//====<[ Struct: t_local ]>=======================
typedef struct s_local
{
	char	*name;
	sem_t	*sem;	
}				t_local;

//====<[ Struct: t_philo ]>=======================
typedef struct s_philo
{
	int				id;
	t_args			*time;
	int				(*actions[3])(struct s_philo *);
	t_local			*local;
	pthread_t		thread;
	t_general		*general;
	int				meals;
	t_ullint		last_meal;
	sem_t			*right;
	sem_t			*left;
	pid_t			pid;
}					t_philo;

//====<[ Struct: t_init ]>========================
typedef struct s_init
{
	t_args			*args;
	t_philo			*phs;
	sem_t			*forks;
	pthread_t		meals_monitor;
}					t_init;

//====<[ Functions: prototypes ]>===============================================

//====<[ Function: philo_init ]>==================
t_init		*dining_philosofers_init(t_init *init, int ac, char **av);
t_args		*get_args(int ac, char **av);
t_philo		*take_seats_around_table(t_init *init);
t_local		*create_local_semaphore(t_philo *p);
sem_t		*put_forks_on_table(t_init *init);
int			set_actions(t_philo *p);
int			start_simulation(t_philo *phs);

//====<[ Function: actions ]>=====================
int			live_cycle(t_philo *p);
int			start_eating(t_philo *p);
int			start_sleeping(t_philo *p);
int			start_thinking(t_philo *p);
void		*live_monitor(void *arg);
void		*meals_monitor(void *arg);

//====<[ Function: utils ]>=======================
int			ft_atoi(char *s);
char		*ft_itoa(int n);
t_ullint	get_current_time(void);
int			clear_table(t_init *init);
void		display_usage_menu(void);
int			ft_strcmp(char *s1, char *s2);
int			my_usleep(t_ullint start, t_ullint duration);
int			print_action(t_philo *p, char *action);
int			clear_lg(t_philo *p);

#endif
//==============================================================================
