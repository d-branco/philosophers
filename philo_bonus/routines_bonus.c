/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:34:15 by abessa-m          #+#    #+#             */
/*   Updated: 2025/03/06 00:51:31 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	am_i_to_sleep(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->n_dead == 0)
		printf("\033[34m%lld %3i is sleeping\033[0m\n",
			get_time(), philosopher->seat);
	else
		return (1);
	sem_post(philosopher->dinner->print);
	will_i_be_dead(philosopher, philosopher->dinner->time_to_zzz);
	return (0);
}

int	am_i_to_think(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->n_dead == 0)
		printf("\033[36m%lld %3i is thinking\033[0m\n",
			get_time(), philosopher->seat);
	else
		return (1);
	sem_post(philosopher->dinner->print);
	if (get_time() + 8
		< philosopher->last_meal_time + philosopher->dinner->time_to_die)
		usleep(4 * 1000);
	return (0);
}

int	am_i_to_eat(t_philosopher *philosopher)
{
	philosopher->last_meal_time = get_time();
	sem_wait(philosopher->dinner->print);
	printf("\033[32m%lld %3i is eating\033[0m",
		philosopher->last_meal_time, philosopher->seat);
	if (philosopher->dinner->verbose)
		printf("\033[32m meal %i\033[0m",
			(philosopher->meals_eaten + 1));
	printf("\n");
	sem_post(philosopher->dinner->print);
	philosopher->meals_eaten++;
	if (philosopher->meals_eaten >= philosopher->dinner->must_eat)
	{
		sem_post(philosopher->dinner->forks);
		usleep(philosopher->dinner->time_to_die * 1000);
		exit (1);
	}
	will_i_be_dead(philosopher, philosopher->dinner->time_to_eat);
	return (0);
}

int	take_fork(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->forks);
	if (am_i_already_dead(philosopher))
		return (1);
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->n_dead == 0)
		printf("\033[35m%lld %3i has taken a fork\n%lld %3i has taken a fork"
			"\033[0m\n", get_time(), philosopher->seat, get_time(),
			philosopher->seat);
	sem_post(philosopher->dinner->print);
	return (0);
}
