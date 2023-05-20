/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:40:29 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/20 19:24:32 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

t_init	*dining_philosofers_init(t_init *init, int ac, char **av)
{
	init->args = get_args(ac, av);
	if (!init->args)
		return (NULL);
	init->phs = take_seats_around_table(init);
	if (!init->phs)
		return (free(init->args), NULL);
	init->forks = put_forks_on_table(init);
	if (!init->forks)
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
	t_print	*print;
	t_meal	*meal;
	int		i;

	init->phs = malloc(sizeof(t_philo) * init->args->philos_nbr);
	print = malloc(sizeof(t_print));
	meal = malloc(sizeof(t_meal));
	if (!init->phs || !print || !meal)
		return (free(init->phs), free(print), free(meal), NULL);
	print->access = TRUE;
	pthread_mutex_init(&print->print_mutex, 0);
	meal->meals = 0;
	pthread_mutex_init(&meal->meal_mutex, 0);
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		(init->phs)[i].id = i + 1;
		(init->phs)[i].time = init->args;
		(init->phs)[i].print = print;
		(init->phs)[i].meal = meal;
		((init->phs)[i].actions)[2 * !((i + 1) % 2)] = &start_eating;
		((init->phs)[i].actions)[(i + 1) % 2] = &start_sleeping;
		((init->phs)[i].actions)[1 + ((i + 1) % 2)] = &start_thinking;
	}
	return (init->phs);
}

t_fork	*put_forks_on_table(t_init *init)
{
	int	i;

	init->forks = malloc(sizeof(t_fork) * init->args->philos_nbr);
	if (!init->forks)
		return (NULL);
	i = -1;
	while (++i < init->args->philos_nbr)
	{
		pthread_mutex_init(&(init->forks)[i].fork, 0);
		(init->forks)[i].status = AVAILABLE;
		(init->phs)[i].right = &(init->forks)[i];
		(init->phs)[i].left = &(init->forks)[(i + 1) % init->args->philos_nbr];
	}
	return (init->forks);
}

int	start_simulation(t_philo *phs)
{
	int	i;

	i = -1;
	while (++i < phs->time->philos_nbr)
		pthread_create(&phs[i].thread, 0, live_cycle, &phs[i]);
	meals_monitor(phs);
	return (0);
}
