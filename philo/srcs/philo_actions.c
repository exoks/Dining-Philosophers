/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:45:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 12:47:57 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*live_cycle(void *args)
{
	t_philo			*p;
	int				action;

	p = (t_philo *) args;
	p->last_meal = get_current_time();
	action = 0;
	while (1)
	{
		if ((p->actions)[action++ % 3](p) == FAILURE)
			break ;
	}
	return (NULL);
}

int	start_eating(t_philo *p)
{
	take_fork(p, p->right);
	if (print_action(p, TAKE_FORK) == FAILURE)
		return (FAILURE);
	take_fork(p, p->left);
	p->last_meal = get_current_time();
	if (print_action(p, EAT) == FAILURE)
		return (FAILURE);
	my_usleep(p, p->last_meal, p->time->time_to_eat);
	p->meals++;
	put_forks(p);
	if (p->meals == p->time->max_meals)
		return (FAILURE);
	return (SUCCESS);
}

int	start_sleeping(t_philo *p)
{
	if (print_action(p, SLEEP) == FAILURE)
		return (FAILURE);
	my_usleep(p, get_current_time(), p->time->time_to_sleep);
	return (SUCCESS);
}

int	start_thinking(t_philo *p)
{
	return (print_action(p, THINK));
}
