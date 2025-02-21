/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:41:09 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 17:03:11 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	clear_table(t_init *init)
{
	clear_lg(init->phs);
	sem_close(init->forks);
	sem_unlink(SEM_FORKS);
	free(init->phs);
	free(init->args);
	return (0);
}

int	clear_lg(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->time->philos_nbr)
	{
		sem_close(p[i].local->sem);
		sem_unlink(p[i].local->name);
		free(p[i].local->name);
		free(p[i].local);
	}
	sem_close(p->general->printer);
	sem_unlink(SEM_PRINTER);
	free(p->general);
	return (SUCCESS);
}
