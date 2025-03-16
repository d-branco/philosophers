/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:31:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/03/06 00:38:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosophize(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->verbose)
		printf("A wild philosopher has appeared at %i\n", philosopher->seat);
	sem_post(philosopher->dinner->print);
	usleep((philosopher->seat % 2) * 2 * 1000);
	while (looping_philosopher(philosopher))
	{
		if (take_fork(philosopher))
			break ;
		if (am_i_to_eat(philosopher))
			break ;
		sem_post(philosopher->dinner->forks);
		if (philosopher->meals_eaten > philosopher->dinner->must_eat)
			break ;
		if (am_i_already_dead(philosopher))
			break ;
		if (am_i_to_sleep(philosopher))
			break ;
		if (am_i_already_dead(philosopher))
			break ;
		if (am_i_to_think(philosopher))
			break ;
	}
}

//sem_wait(philosopher->dinner->print);
//sem_post(philosopher->dinner->print);
int	looping_philosopher(t_philosopher *philosopher)
{
	if (philosopher->dinner->n_philosophers == 1)
	{
		printf("\033[35m%lld %3i has taken a fork\033[0m\n",
			get_time(), philosopher->seat);
		usleep((philosopher->dinner->time_to_die + 1) * 1000);
		am_i_already_dead(philosopher);
		return (0);
	}
	else if ((philosopher->dinner->time_to_die - 3
			<= ((2 + (philosopher->dinner->n_philosophers % 2))
				* philosopher->dinner->time_to_eat))
		&& (philosopher->dinner->n_philosophers == philosopher->seat))
	{
		usleep((philosopher->dinner->time_to_die + philosopher->last_meal_time
				- get_time() + 1) * 1000);
		am_i_already_dead(philosopher);
		return (0);
	}
	return (1);
}

void	will_i_be_dead(t_philosopher *philosopher, long long time_it_takes)
{
	if (time_it_takes + get_time() > philosopher->last_meal_time
		+ philosopher->dinner->time_to_die)
		usleep((philosopher->last_meal_time + philosopher->dinner->time_to_die
				- get_time() + 1) * 1000);
	else
		usleep(time_it_takes * 1000);
}

int	am_i_already_dead(t_philosopher *philosopher)
{
	long long	time_of_death;

	time_of_death = get_time();
	if (time_of_death
		> philosopher->last_meal_time + philosopher->dinner->time_to_die)
	{
		sem_wait(philosopher->dinner->print);
		printf("\033[31m%lld %3i died",
			time_of_death, philosopher->seat);
		if (philosopher->dinner->verbose)
			printf("%4lld miliseconds ago!", time_of_death
				- philosopher->last_meal_time
				- philosopher->dinner->time_to_die);
		printf("\033[0m\n");
		exit (1);
	}
	return (0);
}
