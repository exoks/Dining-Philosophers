/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:00:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 12:30:22 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	ft_atoi(char *s)
{
	int		nb;
	int		i;

	nb = 0;
	i = -!(*s == '-' || *s == '+');
	while (s[++i] && s[i] >= '0' && s[i] <= '9')
		nb = nb * 10 + s[i] - '0';
	return (nb * ((*s != '-') - (*s == '-')));
}

ullint	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0) == 0)
		return (TO_MS(time.tv_sec, time.tv_usec));
	return (0);
}

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
	sem_unlink("forks");
	sem_close(init->phs->semaphores->printer);
	sem_unlink(SEM_PRINTER);
	sem_close(init->phs->semaphores->holder);
	sem_unlink(SEM_HOLDER);
	free(init->phs->semaphores);
	free(init->phs);
	free(init->args);
	return (0);
}

void	display_usage_menu(void)
{
	printf("\nNAME : \n%10s\n", PROGRAM_NAME);
	printf("\nSYNOPSIS : \n%14s %s %s", "./philo_bonus", ARG_1, ARG_2);
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
