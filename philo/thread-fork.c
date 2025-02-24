/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread-fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:59:57 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/21 17:02:40 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	place_first_fork(t_philosopher *philosopher)
{
	int	first_fork;

	first_fork = (philosopher->seat - 1) + ((philosopher->seat - 1) % 2);
	if (first_fork >= philosopher->dinner->n_philosophers)
		first_fork = 0;
	return (first_fork);
}

int	place_second_fork(t_philosopher *philosopher)
{
	int	second_fork;

	second_fork = ((philosopher->seat - 1) + 1) - ((philosopher->seat - 1) % 2);
	if (second_fork >= philosopher->dinner->n_philosophers)
		second_fork = 0;
	return (second_fork);
}

int	take_fork_one_or_die_trying(t_philosopher *philosopher, int first_fork)
{
	pthread_mutex_lock(&philosopher->dinner->forks[first_fork]);
	if (am_i_already_dead(philosopher))
	{
		pthread_mutex_unlock(&philosopher->dinner->forks[first_fork]);
		return (1);
	}
	pthread_mutex_lock(&philosopher->dinner->print_mutex);
	if (!philosopher->dinner->n_dead)
	{
		printf("\033[35m%lld %3i has taken a fork\033[0m",
			get_time(), philosopher->seat);
		if (philosopher->dinner->verbose)
			printf("\033[35m%4i\033[0m", first_fork);
		printf("\n");
	}
	pthread_mutex_unlock(&philosopher->dinner->print_mutex);
	return (0);
}

int	take_fork_two_or_die_trying(t_philosopher *philosopher, int f1, int f2)
{
	pthread_mutex_lock(&philosopher->dinner->forks[f2]);
	if (am_i_already_dead(philosopher))
	{
		pthread_mutex_unlock(&philosopher->dinner->forks[f1]);
		pthread_mutex_unlock(&philosopher->dinner->forks[f2]);
		return (1);
	}
	pthread_mutex_lock(&philosopher->dinner->print_mutex);
	if (!philosopher->dinner->n_dead)
	{
		printf("\033[35m%lld %3i has taken a fork\033[0m",
			get_time(), philosopher->seat);
		if (philosopher->dinner->verbose)
			printf("\033[35m%4i\033[0m", f2);
		printf("\n");
	}
	return (0);
}

void	drop_the_forks(t_philosopher *philosopher, int f1, int f2)
{
	pthread_mutex_unlock(&philosopher->dinner->forks[f1]);
	pthread_mutex_unlock(&philosopher->dinner->forks[f2]);
}
