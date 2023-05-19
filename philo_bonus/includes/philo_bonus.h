/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:29:30 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 22:47:33 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# define TO_MS(A, B) (A * 1000) + (B / 1000)

//###############################
//#            MENU             #
//###############################
# define PROGRAM_NAME "philo_bonus"
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

//###############################
//#          ACTIONS            #
//###############################
# define EAT "%llu %d is eating\n"
# define THINK "%llu %d is thinking\n"
# define SLEEP "%llu %d is sleeping\n"
# define DIE "%llu %d died\n"
# define TAKE_FORK "%llu %d has taken a fork\n"

//##############################
//#        EXIT_STATUS         #
//##############################
# define FAILURE 1
# define SUCCESS 0

//##############################
//#       LOGICAL VALUES       #
//##############################
# define FALSE 0
# define TRUE 1

//##############################
//#       PHILO STATUS         #
//##############################
# define DIED 2
# define ALIVE 3 

//##############################
//#         SIMAPHORES         #
//##############################
# define SEM_PRINTER "sem_print"
# define SEM_MEALS "sem_meals"
# define SEM_FORKS "sem_forks"

typedef unsigned long long int ullint;

typedef struct t_args
{
	int				philos_nbr;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				max_meals;
}					t_args;

typedef struct s_semaphore
{
	sem_t			*printer;
	sem_t			*meals;
}					t_semaphore;

typedef struct s_local
{
	char	*name;
	sem_t	*sem;	
}				t_local;

typedef struct s_philo
{
	int				id;
	t_args			*time;
	int				(*actions[3])(struct s_philo *);
	t_local			*local;
	pthread_t		thread;
	t_semaphore		*semaphores;
	ullint			last_meal;
	sem_t			*right;
	sem_t			*left;
	pid_t			pid;
}					t_philo;

typedef struct s_init
{
	t_args			*args;
	t_philo			*phs;
	sem_t			*forks;
	pthread_t		meals_monitor;
}					t_init;

	/******** PHILO_INIT *********/
t_init	*dining_philosofers_init(t_init *init, int ac, char **av);
t_args	*get_args(int ac, char **av);
t_philo	*take_seats_around_table(t_init *init);
sem_t	*put_forks_on_table(t_init *init);
int		start_simulation(t_philo *phs);

	/********** ACTIONS **********/
int		live_cycle(t_philo *p);
int		start_eating(t_philo *p);
int		start_thinking(t_philo *p);
int		start_sleeping(t_philo *p);
void	*monitoring_live(void *arg);
void	*meals_monitor(void *arg);

	/********** PHILO_UTILS ******/
int		take_forks(t_philo *p);
int		put_forks(t_philo *p);

	/*********** Utils ***********/
int		ft_atoi(char *s);
char	*ft_itoa(int n);
ullint	get_current_time();
int		clear_table(t_init *init);
void	display_usage_menu(void);
int		ft_strcmp(char *s1, char *s2);
int		my_usleep(ullint start, ullint duration);

#endif
