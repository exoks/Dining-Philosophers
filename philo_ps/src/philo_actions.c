/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:45:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 16:49:20 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//====<[ live_cycle: ]>=========================================================
int	live_cycle(t_philo *p)
{
	int	action;

	sem_wait(p->local->sem);
	pthread_create(&p->thread, 0, &live_monitor, p);
	while (get_current_time() < p->last_meal)
		usleep(200);
	sem_post(p->local->sem);
	sem_wait(p->local->sem);
	p->last_meal = get_current_time();
	sem_post(p->local->sem);
	action = 0;
	while (1)
		(p->actions)[action++ % 3](p);
	return (0);
}

//====<[ start_eating: ]>=======================================================
int	start_eating(t_philo *p)
{
	sem_wait(p->right);
	print_action(p, TAKE_FORK);
	sem_wait(p->left);
	sem_wait(p->local->sem);
	p->last_meal = get_current_time();
	sem_post(p->local->sem);
	print_action(p, EAT);
	my_usleep(p->last_meal, p->time->time_to_eat);
	p->meals++;
	sem_post(p->right);
	sem_post(p->left);
	if (p->meals == p->time->max_meals)
		sem_post(p->general->meals);
	return (SUCCESS);
}

//====<[ start_thinking: ]>=====================================================
int	start_thinking(t_philo *p)
{
	print_action(p, THINK);
	return (SUCCESS);
}

//====<[ start_sleeping: ]>=====================================================
int	start_sleeping(t_philo *p)
{
	t_ullint	time;

	time = get_current_time();
	print_action(p, SLEEP);
	my_usleep(time, p->time->time_to_sleep);
	return (SUCCESS);
}

//====<[ live_monitor: ]>=======================================================
void	*live_monitor(void *arg)
{
	t_philo		*p;

	p = (t_philo *) arg;
	sem_wait(p->local->sem);
	sem_post(p->local->sem);
	while (1)
	{
		sem_wait(p->local->sem);
		if (get_current_time() - p->last_meal >= (t_ullint)p->time->time_to_die)
		{
			sem_wait(p->general->printer);
			printf(DIE, get_current_time(), p->id);
			exit(DIED);
		}
		sem_post(p->local->sem);
		usleep(350);
	}
	return (NULL);
}
