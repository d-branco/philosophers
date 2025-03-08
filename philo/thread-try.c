/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread-try.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:04:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/03/03 13:51:14 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophize_or_die_trying(t_philosopher *philosopher, int f1, int f2)
{
	while (1)
	{
		if (take_fork_one_or_die_trying(philosopher, f1))
			break ;
		if (take_fork_two_or_die_trying(philosopher, f1, f2))
			break ;
		if (eat_or_die_trying(philosopher, f1, f2))
			break ;
		drop_the_forks(philosopher, f1, f2);
		if (am_i_already_dead(philosopher))
			break ;
		if (sleep_or_die_trying(philosopher))
			break ;
		if (am_i_already_dead(philosopher))
			break ;
		if (think_or_die_trying(philosopher))
			break ;
	}
}

int	eat_or_die_trying(t_philosopher *philosopher, int f1, int f2)
{
	philosopher->last_meal_time = get_time();
	if (!philosopher->dinner->n_dead)
	{
		printf("\033[32m%lld %3i is eating\033[0m",
			philosopher->last_meal_time, philosopher->seat);
		if (philosopher->dinner->verbose)
			printf("\033[32m meal %i\033[0m",
				(philosopher->meals_eaten + 1));
		printf("\n");
	}
	else
	{
		drop_the_forks(philosopher, f1, f2);
		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->dinner->print_mutex);
	philosopher->meals_eaten++;
	if (philosopher->meals_eaten >= philosopher->dinner->must_eat)
	{
		drop_the_forks(philosopher, f1, f2);
		return (1);
	}
	will_i_be_dead(philosopher, philosopher->dinner->time_to_eat);
	return (0);
}

int	sleep_or_die_trying(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->dinner->print_mutex);
	if (!philosopher->dinner->n_dead)
		printf("\033[34m%lld %3i is sleeping\033[0m\n",
			get_time(), philosopher->seat);
	else
	{
		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->dinner->print_mutex);
	will_i_be_dead(philosopher, philosopher->dinner->time_to_zzz);
	return (0);
}

int	think_or_die_trying(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->dinner->print_mutex);
	if (!philosopher->dinner->n_dead)
		printf("\033[36m%lld %3i is thinking\033[0m\n",
			get_time(), philosopher->seat);
	else
	{
		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->dinner->print_mutex);
	if (get_time() + 8
		< philosopher->last_meal_time + philosopher->dinner->time_to_die)
		usleep(4 * 1000);
	return (0);
}
