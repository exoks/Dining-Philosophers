/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:45:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 15:46:16 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	print_action(t_philo *p, char *action);

int	live_cycle(t_philo *p)
{
	int				action;
	ullint			tmp;

	pthread_create(&p->thread, 0, &monitoring_live, p);	
	while (get_current_time() < p->last_meal)
		usleep(200);
	sem_post(p->semaphores->holder);
	tmp = get_current_time();
	sem_wait(p->local->sem);
	p->last_meal = tmp;
	sem_post(p->local->sem);
	action = 0;
	while (1)
	{
		if ((p->actions)[action++ % 3](p) == ALIVE)
			return (ALIVE);
	}
	return (0);
}

int	start_eating(t_philo *p)
{
	ullint	tmp;

	sem_wait(p->right);
	print_action(p, TAKE_FORK);
	sem_wait(p->left);
	tmp = get_current_time();
	sem_wait(p->local->sem);
	p->last_meal = tmp;
	sem_post(p->local->sem);
	print_action(p, EAT);
	my_usleep(p->last_meal, p->time->time_to_eat);
	p->meals++;
	sem_post(p->right);
	sem_post(p->left);
	if (p->meals == p->time->max_meals)
		return (ALIVE);
	return (SUCCESS);
}

int	start_thinking(t_philo *p)
{
	print_action(p, THINK);
	return (SUCCESS);
}

int	start_sleeping(t_philo *p)
{
	ullint	time;

	time = get_current_time();
	print_action(p, SLEEP);
	my_usleep(time, p->time->time_to_sleep); 
	return (SUCCESS);
}

int	print_action(t_philo *p, char *action)
{
	sem_wait(p->semaphores->printer);
	printf(action, get_current_time(), p->id);
	sem_post(p->semaphores->printer);
	return (SUCCESS);
}

int	my_usleep(ullint start, ullint duration)
{
	while (get_current_time() - start < duration)
		usleep(200);
	return (SUCCESS);
}

void	*monitoring_live(void *arg)
{
	t_philo *p;
//	ullint	tmp;

	p = (t_philo *) arg;
	sem_wait(p->semaphores->holder);
	sem_post(p->semaphores->holder);
	while (1)
	{
		//tmp = get_current_time() - p->last_meal;
		sem_wait(p->local->sem);
		if (get_current_time() - p->last_meal >= (ullint) p->time->time_to_die)
		{
			sem_wait(p->semaphores->printer);
			printf(DIE, get_current_time(), p->id);
			exit(DIED);
		}
		sem_post(p->local->sem);
		usleep(200);
	}
	return (NULL);
}
