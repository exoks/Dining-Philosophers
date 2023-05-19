/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:01:08 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 12:36:42 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	my_usleep(t_philo *p, t_ullint start, t_ullint duration)
{
	while (get_current_time() - start < duration)
	{
		if (get_current_time() - p->last_meal >= (t_ullint)p->time->time_to_die)
			return (print_action(p, DIE));
		usleep(200);
	}
	return (SUCCESS);
}

int	print_action(t_philo *phs, char *action)
{
	pthread_mutex_lock(&phs->print->print);
	if (phs->print->access == FALSE)
	{
		pthread_mutex_unlock(&phs->print->print);
		return (FAILURE);
	}
	printf(action, get_current_time(), phs->id);
	if (ft_strcmp(action, DIE) == 0)
		phs->print->access = FALSE;
	pthread_mutex_unlock(&phs->print->print);
	return (SUCCESS);
}

int	put_forks(t_philo *p)
{
	pthread_mutex_lock(&p->right->fork);
	p->right->status = AVAILABLE;
	pthread_mutex_unlock(&p->right->fork);
	pthread_mutex_lock(&p->left->fork);
	p->left->status = AVAILABLE;
	pthread_mutex_unlock(&p->left->fork);
	return (SUCCESS);
}

int	take_fork(t_philo *p, t_fork *fork)
{
	while (1)
	{
		pthread_mutex_lock(&fork->fork);
		if (get_current_time() - p->last_meal >= (t_ullint)p->time->time_to_die)
		{
			print_action(p, DIE);
			break ;
		}
		if (fork->status == AVAILABLE)
		{
			fork->status = TAKEN;
			break ;
		}
		pthread_mutex_unlock(&fork->fork);
		usleep(100);
	}
	pthread_mutex_unlock(&fork->fork);
	return (0);
}
