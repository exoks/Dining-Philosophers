/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:29:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/19 11:07:51 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

int	ft_nb_size(long int nb)
{
	if (nb)
		return (1 + ft_nb_size(nb / 10));
	return (0);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nb;

	nb = (long int) n;
	len = ft_nb_size(nb) + 1;
	if (nb <= 0)
	{
		nb *= -1;
		++len;
	}
	str = (char *) malloc (len);
	if (!str)
		return (0);
	str[len - 1] = 0;
	str[0] = '-';
	if (nb == 0)
		str[0] = '0';
	len = len - 2;
	while (nb > 0)
	{
		str[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
