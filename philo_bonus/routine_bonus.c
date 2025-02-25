/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:31:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/25 14:54:48 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	take_fork(t_philosopher *philosopher);
int	am_i_already_dead(t_philosopher *philosopher);

void	philosophize(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->verbose)
		printf("A wild philosopher has appeared at %i\n", philosopher->seat);
	sem_post(philosopher->dinner->print);
	while (1)
	{

		
		//take fork
		if (take_fork(philosopher))
			break ;
			//am i dead


		//eat
		philosopher->last_meal_time = get_time();
		sem_wait(philosopher->dinner->print);
		printf("%lld %d is eating\n",
			philosopher->last_meal_time, philosopher->seat);
		sem_post(philosopher->dinner->print);
		philosopher->meals_eaten++;
		usleep(philosopher->dinner->time_to_eat * 1000);
		//am i dead

		
		//dro-drop the forks
		sem_post(philosopher->dinner->forks);
		if (philosopher->meals_eaten > philosopher->dinner->must_eat)
			break ;

			
		//sleep
		sem_wait(philosopher->dinner->print);
		printf("%lld %d is sleeping\n", get_time(), philosopher->seat);
		sem_post(philosopher->dinner->print);
		usleep(philosopher->dinner->time_to_zzz * 1000);
			//am i dead

		
		//think
		sem_wait(philosopher->dinner->print);
		printf("%lld %d is thinking\n", get_time(), philosopher->seat);
		sem_post(philosopher->dinner->print);
	}
}

int	take_fork(t_philosopher *philosopher)
{
	sem_wait(philosopher->dinner->forks);
	if (am_i_already_dead(philosopher))
	{
		sem_post(philosopher->dinner->forks);
		return (1);
	}
	sem_wait(philosopher->dinner->print);
	if (philosopher->dinner->n_dead == 0)
	{
		printf("\033[35m%lld %3i has taken a fork\n%lld %3i has taken a fork"
			"\033[0m\n", get_time(), philosopher->seat, get_time(),
			philosopher->seat);
	}
	sem_post(philosopher->dinner->print);
	return (0);
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

//
//int	eat_or_die_trying(t_philosopher *philosopher, int f1, int f2)
//{
//	philosopher->last_meal_time = get_time();
//	if (!philosopher->dinner->n_dead)
//	{
//		printf("\033[32m%lld %3i is eating\033[0m",
//			philosopher->last_meal_time, philosopher->seat);
//		if (philosopher->dinner->verbose)
//			printf("\033[32m meal %i\033[0m",
//				(philosopher->meals_eaten + 1));
//		printf("\n");
//	}
//	else
//	{
//		drop_the_forks(philosopher, f1, f2);
//		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
//		return (1);
//	}
//	pthread_mutex_unlock(&philosopher->dinner->print_mutex);
//	philosopher->meals_eaten++;
//	if (philosopher->meals_eaten >= philosopher->dinner->must_eat)
//	{
//		drop_the_forks(philosopher, f1, f2);
//		return (1);
//	}
//	will_i_be_dead(philosopher, philosopher->dinner->time_to_eat);
//	return (0);
//}