/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:29:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/20 18:46:06 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo_bonus.h"

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

int	my_usleep(t_ullint start, t_ullint duration)
{
	while (get_current_time() - start < duration)
		usleep(200);
	return (SUCCESS);
}

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
