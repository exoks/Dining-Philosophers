/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:40:29 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 15:27:31 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

t_local	*create_local_semaphore(t_philo *p);

t_init	*dining_philosofers_init(t_init *init, int ac, char **av)
{
	init->args = get_args(ac, av);
	if (!init->args)
		return (NULL);
	init->phs = take_seats_around_table(init);
	if (!init->phs)
		return (free(init->args), NULL);
	init->forks = put_forks_on_table(init);
	if (init->forks == SEM_FAILED)
		return (free(init->args), free(init->phs), NULL);
	return (init);
}

t_args	*get_args(int ac, char **av)
{
	t_args	*args;

	if (!(ac == 5 || ac == 6))
		return (NULL);
	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	args->philos_nbr = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->max_meals = -1;
	if (args->philos_nbr <= 0 || args->time_to_eat < 0 || args->time_to_sleep < 0
			|| args->time_to_die < 0)
		return (free(args), NULL);
	if (av[5])
	{
		args->max_meals = ft_atoi(av[5]);
		if (args->max_meals <= 0)
			return (free(args), NULL);
	}
	return (args);
}

t_philo	*take_seats_around_table(t_init *init)
{
	t_semaphore	*semaphores;
	int			i;
	
	init->phs = malloc(sizeof(t_philo) * init->args->philos_nbr);
	semaphores = malloc(sizeof(t_semaphore));
	if (!init->phs || !semaphores)
		return (free(init->phs), free(semaphores), NULL);
	sem_unlink(SEM_PRINTER);
	semaphores->printer = sem_open(SEM_PRINTER, O_CREAT, 0777, 1);
	sem_unlink(SEM_HOLDER);
	semaphores->holder = sem_open(SEM_HOLDER, O_CREAT, 0777, 0);
//	if (print->print == SEM_FAILED)
//		return (free(init->phs), free(print), NULL);
	// need protection
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		(init->phs)[i].id = i + 1;
		(init->phs)[i].local = create_local_semaphore(&(init->phs)[i]);
		// need protection
		(init->phs)[i].time = init->args;
		(init->phs)[i].meals = 0;
		(init->phs)[i].semaphores = semaphores;
		((init->phs)[i].actions)[2 * !((i + 1) % 2)] = &start_eating;
		((init->phs)[i].actions)[(i + 1) % 2] = &start_sleeping;
		((init->phs)[i].actions)[1 + ((i + 1) % 2)] = &start_thinking;
	}
	return (init->phs);
}

t_local	*create_local_semaphore(t_philo *p)
{
	p->local = malloc(sizeof(t_local));
	if (!p->local)
		return (NULL);
	p->local->name = ft_itoa(p->id);
	if (!p->local->name)
		return (free(p->local), NULL);
	sem_unlink(p->local->name);
	p->local->sem = sem_open(p->local->name, O_CREAT, 0777, 1);
	sem_unlink(p->local->name);
	if (p->local->sem == SEM_FAILED)
		return (free(p->local->name), free(p->local), NULL);
	return (p->local);
}

sem_t	*put_forks_on_table(t_init *init)
{
	int		i;

	sem_unlink("forks");
	init->forks = sem_open("forks", O_CREAT, 0777, init->args->philos_nbr);
	if (init->forks == SEM_FAILED)
		return (SEM_FAILED);
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		(init->phs)[i].right = init->forks; 
		(init->phs)[i].left = init->forks;
	}
	return (init->forks);
}

int	start_simulation(t_philo *phs)
{
	int		i;
	int		status;
	ullint	start;

	start = get_current_time() + 200;
	i = -1;
	while (++i < phs->time->philos_nbr)
	{
		phs[i].last_meal = start;
		phs[i].pid = fork();
		if (phs[i].pid == -1)
			return (0);
		if (phs[i].pid == 0)
		{
			live_cycle(&phs[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < phs->time->philos_nbr)
	{
		waitpid(-1, &status, 0);
		if (((char *) &status)[1] == DIED)
			break ;
	}
	i = -1;
	while (++i < phs->time->philos_nbr)
		kill(phs[i].pid, SIGKILL);
	return (0);
}
