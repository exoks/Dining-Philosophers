/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:40:29 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 17:03:21 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

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
	args->max_meals = -(av[5] == NULL) + (av[5] != NULL) * ft_atoi(av[5]);
	if (args->philos_nbr <= 0 || args->time_to_eat < 0 || args->time_to_die < 0
		|| args->time_to_sleep < 0 || (av[5] && args->max_meals <= 0))
		return (free(args), NULL);
	return (args);
}

t_philo	*take_seats_around_table(t_init *init)
{
	t_general	*general;
	int			i;

	init->phs = malloc(sizeof(t_philo) * init->args->philos_nbr);
	general = malloc(sizeof(t_general));
	if (!init->phs || !general)
		return (free(init->phs), free(general), NULL);
	sem_unlink(SEM_PRINTER);
	general->printer = sem_open(SEM_PRINTER, O_CREAT, 0777, 1);
	sem_unlink(SEM_MEALS);
	general->meals = sem_open(SEM_MEALS, O_CREAT, 0777, 0);
	if (general->printer == SEM_FAILED || general->meals == SEM_FAILED)
		return (free(init->phs), free(general), NULL);
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		(init->phs)[i].id = i + 1;
		(init->phs)[i].local = create_local_semaphore(&(init->phs)[i]);
		if (!(init->phs)[i].local)
			return (clear_lg(init->phs), free(init->phs), NULL);
		(init->phs)[i].time = init->args;
		(init->phs)[i].general = general;
		set_actions(&(init->phs)[i]);
	}
	return (init->phs);
}

sem_t	*put_forks_on_table(t_init *init)
{
	int		i;

	sem_unlink(SEM_FORKS);
	init->forks = sem_open(SEM_FORKS, O_CREAT, 0777, init->args->philos_nbr);
	if (init->forks == SEM_FAILED)
		return (SEM_FAILED);
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		(init->phs)[i].meals = 0;
		(init->phs)[i].right = init->forks;
		(init->phs)[i].left = init->forks;
	}
	return (init->forks);
}

int	start_simulation(t_philo *phs)
{
	t_ullint	start;
	int			i;

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
			exit(1);
		}
	}
	waitpid(-1, 0, 0);
	i = -1;
	while (++i < phs->time->philos_nbr)
		kill(phs[i].pid, SIGKILL);
	return (0);
}
