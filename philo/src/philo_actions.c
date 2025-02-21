/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:45:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 15:13:32 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//====<[ live_cycle: ]>=========================================================
void	*live_cycle(void *args)
{
	t_philo			*p;
	int				action;

	p = (t_philo *) args;
	p->last_meal = get_current_time();
	action = 0;
	while (1)
		if ((p->actions)[action++ % 3](p) == FAILURE)
			break ;
	return (NULL);
}

//====<[ start_eating: ]>=======================================================
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
	pthread_mutex_lock(&p->meal->meal_mutex);
	p->meal->meals++;
	pthread_mutex_unlock(&p->meal->meal_mutex);
	put_forks(p);
	return (SUCCESS);
}

//====<[ start_sleeping: ]>=====================================================
int	start_sleeping(t_philo *p)
{
	if (print_action(p, SLEEP) == FAILURE)
		return (FAILURE);
	my_usleep(p, get_current_time(), p->time->time_to_sleep);
	return (SUCCESS);
}

//====<[ start_thinking: ]>=====================================================
int	start_thinking(t_philo *p)
{
	return (print_action(p, THINK));
}

//====<[ meals_monitor: ]>======================================================
int	meals_monitor(t_philo *p)
{
	int		total;

	total = p->time->philos_nbr * p->time->max_meals;
	while (1)
	{
		pthread_mutex_lock(&p->meal->meal_mutex);
		pthread_mutex_lock(&p->print->print_mutex);
		if (p->print->access == FALSE)
		{
			pthread_mutex_unlock(&p->print->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->print->print_mutex);
		if (p->meal->meals >= total)
		{
			pthread_mutex_lock(&p->print->print_mutex);
			p->print->access = FALSE;
			pthread_mutex_unlock(&p->print->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->meal->meal_mutex);
	}
	pthread_mutex_unlock(&p->meal->meal_mutex);
	return (SUCCESS);
}
