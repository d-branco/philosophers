/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/20 16:09:43 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_thread(void *arg)
{
	t_philosopher	philosophers;

	philosophers = *(t_philosopher *)arg;
	if (philosophers.dinner->verbose)
	{
		pthread_mutex_lock(&philosophers.dinner->print_mutex);
		printf("\033[1;93mverbose:\033[0m seat%3i "
			"A wild philosopher appears!\n", philosophers.seat);
		pthread_mutex_unlock(&philosophers.dinner->print_mutex);
	}
	return (arg);
}
