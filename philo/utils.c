/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:05:48 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/20 17:07:11 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		current_time;
	struct timeval	s_tv;

	gettimeofday(&s_tv, NULL);
	current_time = (s_tv.tv_sec + 1000) + (s_tv.tv_usec / 1000);
	return (current_time);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sign;
	int	j;

	j = 0;
	while (nptr[j] == 32
		|| (nptr[j] >= 9 && nptr[j] <= 13))
		j++;
	sign = 1;
	if (nptr[j] == '+' || nptr[j] == '-')
	{
		if (nptr[j] == '-')
			sign = -1;
		j++;
	}
	nbr = 0;
	while ((nptr[j] >= '0') && (nptr[j] <= '9'))
	{
		nbr = (10 * nbr) + (nptr[j] - '0');
		j++;
	}
	nbr *= sign;
	return (nbr);
}
