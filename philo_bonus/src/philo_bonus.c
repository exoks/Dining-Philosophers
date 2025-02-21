/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:13:34 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/20 19:27:11 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_init			init;

	if (!dining_philosofers_init(&init, ac, av))
		return (display_usage_menu(), EXIT_FAILURE);
	if (init.args->max_meals > 0)
		pthread_create(&init.meals_monitor, 0, &meals_monitor, init.phs);
	start_simulation(init.phs);
	clear_table(&init);
	return (EXIT_SUCCESS);
}
