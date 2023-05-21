/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:41:09 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/21 12:22:34 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	clear_table(t_init *init)
{
	int	i;

	i = -1;
	while (++i < init->args->philos_nbr)
	{
		sem_close((init->phs)[i].local->sem);
		sem_unlink((init->phs)[i].local->name);
		free((init->phs)[i].local->name);
		free((init->phs)[i].local);
	}
	sem_close(init->forks);
	sem_unlink(SEM_FORKS);
	sem_close(init->phs->general->printer);
	sem_unlink(SEM_PRINTER);
	free(init->phs->general);
	free(init->phs);
	free(init->args);
	return (0);
}
