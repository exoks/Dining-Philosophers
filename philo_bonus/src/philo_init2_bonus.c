/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:00:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 17:07:28 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

//====<[ display_usage_menu: ]>=================================================
void	display_usage_menu(void)
{
	printf("\nNAME : \n%18s\n", PROGRAM_NAME);
	printf("\nSYNOPSIS : \n%20s %s %s", "./philo_bonus", ARG_1, ARG_2);
	printf("%s %s %s\n", ARG_3, ARG_4, ARG_5);
	printf("\nDESCRIPTION : \n");
	printf("%31s : %s\n", ARG_1, ARG_1_USAGE);
	printf("%20s : %s\n", ARG_2, ARG_USAGE);
	printf("%20s : %s\n", ARG_3, ARG_USAGE);
	printf("%22s : %s\n", ARG_4, ARG_USAGE);
	printf("%50s : %s\n", ARG_5, ARG_5_USAGE);
	printf("\nRETURN VALUES: \n");
	printf("\t%s %s\n", FAILURE_REASON, FAILURE_ACTION);
	printf("\t%s %s\n\n", SUCCESS_ACTION, SUCCESS_REASON);
}

//====<[ set_actions: ]>========================================================
int	set_actions(t_philo *p)
{
	(p->actions)[2 * !(p->id % 2)] = &start_eating;
	(p->actions)[p->id % 2] = &start_sleeping;
	(p->actions)[1 + (p->id % 2)] = &start_thinking;
	return (SUCCESS);
}

//====<[ print_action: ]>=======================================================
int	print_action(t_philo *p, char *action)
{
	sem_wait(p->general->printer);
	printf(action, get_current_time(), p->id);
	sem_post(p->general->printer);
	return (SUCCESS);
}

//====<[ create_local_semaphore: ]>=============================================
t_local	*create_local_semaphore(t_philo *p)
{
	t_local	*local;

	local = malloc(sizeof(t_local));
	if (!local)
		return (NULL);
	local->name = ft_itoa(p->id);
	if (!local->name)
		return (free(local), NULL);
	sem_unlink(local->name);
	local->sem = sem_open(local->name, O_CREAT, 0777, 1);
	if (local->sem == SEM_FAILED)
		return (free(local->name), free(local), NULL);
	return (local);
}

//====<[ meals_monitor: ]>======================================================
void	*meals_monitor(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *) arg;
	i = 0;
	while (++i)
	{
		sem_wait(p->general->meals);
		if (i == p->time->philos_nbr)
			break ;
		usleep(200);
	}
	kill(p->pid, SIGKILL);
	return (NULL);
}
