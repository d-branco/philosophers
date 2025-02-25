/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:31:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/25 16:29:06 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_philosopher *philosopher);
int	am_i_already_dead(t_philosopher *philosopher);
void	will_i_be_dead(t_philosopher *philosopher, long long time_it_takes);
int	am_i_to_eat(t_philosopher *philosopher);
int	am_i_to_sleep(t_philosopher *philosopher);
int	am_i_to_think(t_philosopher *philosopher);

void	philosophize(t_philosopher *philosopher)
{
	usleep((philosopher->seat % 2) * 1000);
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->verbose)
		printf("A wild philosopher has appeared at %i\n", philosopher->seat);
	sem_post(philosopher->dinner->print);
	while (1)
	{

		
		//take fork
		if (take_fork(philosopher))
			break ;
		//eat
		if (am_i_to_eat(philosopher))
			break ;		
		//am i dead

		
		//dro-drop the forks
		sem_post(philosopher->dinner->forks);
		if (philosopher->meals_eaten > philosopher->dinner->must_eat)
			break ;
		
		//am i dead
		if (am_i_already_dead(philosopher))
			break ;

			
		//sleep
		if (am_i_to_sleep(philosopher))
			break ;
		
		//am i dead
		if (am_i_already_dead(philosopher))
			break ;

		
		//think
		if (am_i_to_think(philosopher))
			break ;
	}
}


int	am_i_to_sleep(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->print);
	if (!philosopher->dinner->n_dead)
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
	if (!philosopher->dinner->n_dead)
		printf("\033[36m%lld %3i is thinking\033[0m\n",
			get_time(), philosopher->seat);
	else
		return (1);
	sem_post(philosopher->dinner->print);
	if (get_time() + 100
		< philosopher->last_meal_time	+ philosopher->dinner->time_to_die)
		usleep(5000);
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
		return (1);
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

void	will_i_be_dead(t_philosopher *philosopher, long long time_it_takes)
{
	if (time_it_takes + get_time() > philosopher->last_meal_time
		+ philosopher->dinner->time_to_die)
		usleep(time_it_takes + get_time() - philosopher->last_meal_time
			- philosopher->dinner->time_to_die);
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
		if (philosopher->dinner->n_dead == 0)
		{
			philosopher->dinner->n_dead = philosopher->dinner->n_dead + 1;
			printf("\033[31m%lld %3i died",
				time_of_death, philosopher->seat);
			if (philosopher->dinner->verbose)
				printf("%4lld miliseconds ago!", time_of_death
					- philosopher->last_meal_time
					- philosopher->dinner->time_to_die);
			printf("\033[0m\n");
		}
		//sem_post(philosopher->dinner->print);
		return (1);
	}
	return (0);
}
