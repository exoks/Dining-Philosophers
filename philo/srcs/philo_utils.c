/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:00:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/20 20:43:31 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(char *s)
{
	int		nb;
	int		i;

	if (!s)
		return (0);
	nb = 0;
	i = -!(*s == '-' || *s == '+');
	while (s[++i] && s[i] >= '0' && s[i] <= '9')
		nb = nb * 10 + s[i] - '0';
	return (nb * ((*s != '-') - (*s == '-')));
}

t_ullint	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, 0) == 0)
		return (TO_MS(time.tv_sec, time.tv_usec));
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i] || s2[i])
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

int	clear_table(t_init *init)
{
	int	i;

	i = -1;
	while (++i < init->phs->time->philos_nbr)
		pthread_mutex_destroy(&(init->forks)[i].fork);
//	pthread_mutex_destroy(&init->phs->print->print_mutex);
	pthread_mutex_destroy(&init->phs->meal->meal_mutex);
	free(init->phs->print);
	free(init->phs->meal);
	free(init->forks);
	free(init->phs);
	free(init->args);
	return (0);
}

void	display_usage_menu(void)
{
	printf("\nNAME : \n%10s\n", PROGRAM_NAME);
	printf("\nSYNOPSIS : \n%14s %s %s", "./philo", ARG_1, ARG_2);
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
