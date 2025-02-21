/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/21 11:00:27 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_already_dead(t_philosopher philosopher);

//	struct s_philosopher
//		t_dinner	*dinner;
//		int			seat;
//		int			meals_eaten;
//		long long	last_meal_time;
//Function to test timestamps:
//	usleep(philosopher.seat * 100 * 1000);
void	*philosopher_thread(void *arg)
{
	t_philosopher	philosopher;
	int				enter_loop;
	int				first_fork_position;
	int				second_fork_position;

	philosopher = *(t_philosopher *)arg;

	first_fork_position = (philosopher.seat - 1) + ((philosopher.seat - 1) % 2);
	if (first_fork_position >= philosopher.dinner->n_philosophers)
		first_fork_position = 0;
	second_fork_position = ((philosopher.seat - 1) + 1) - ((philosopher.seat - 1) % 2);
	if (second_fork_position >= philosopher.dinner->n_philosophers)
		second_fork_position = 0;

	enter_loop = 1;
	if (philosopher.dinner->verbose)
	{
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[1;93mseat%3i:\033[0m  "
				"A wild philosopher appears!\n", philosopher.seat);
			if (philosopher.dinner->verbose)
			{
				printf("\033[1;93mseat%3i:\033[0m  takes forks:%4i, and%4i\n",
					philosopher.seat, first_fork_position, second_fork_position);
			}
		}
		else
			enter_loop = 0;
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	}

	philosopher.last_meal_time = get_time();
	
	// if time_to_die < time_to_zz!
	// only one
	while (enter_loop)
	{
		//take left fork
		pthread_mutex_lock(&philosopher.dinner->forks[first_fork_position]);
		//am i already dead?
		if (am_i_already_dead(philosopher))
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork_position]);
			break;
		}
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[35m%lld %3i has taken a fork\033[0m",
				get_time(), philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[35m%4i\033[0m", first_fork_position);
			printf("\n");
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);

		//take righ fork
		pthread_mutex_lock(&philosopher.dinner->forks[second_fork_position]);
		//am i already dead?
		if (am_i_already_dead(philosopher))
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork_position]);
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork_position]);
			break;
		}
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[35m%lld %3i has taken a fork\033[0m",
				get_time(), philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[35m%4i\033[0m", second_fork_position);
			printf("\n");
		}
		//pthread_mutex_unlock(&philosopher.dinner->print_mutex);

		//eat
		//pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[32m%lld %3i is eating\033[0m",
				get_time(), philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[32m meal %i\033[0m", (philosopher.meals_eaten + 1));
			printf("\n");
		}
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork_position]); //first one
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork_position]);
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		philosopher.meals_eaten++;
		if (philosopher.meals_eaten >= philosopher.dinner->must_eat)
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork_position]); //first one
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork_position]);
			break ;
		}
		philosopher.last_meal_time = get_time();
		usleep(philosopher.dinner->time_to_eat * 1000);
		//release the forks
		pthread_mutex_unlock(&philosopher.dinner->forks[first_fork_position]); //first one
		pthread_mutex_unlock(&philosopher.dinner->forks[second_fork_position]);
		//sleep
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
			printf("\033[34m%lld %3i is sleeping\033[0m\n",
				get_time(), philosopher.seat);
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		usleep(philosopher.dinner->time_to_zzz * 1000);
			//am i already dead?
		if (am_i_already_dead(philosopher))
			break;
	}
	return (arg);
}

int	am_i_already_dead(t_philosopher philosopher)
{
	if (get_time() > philosopher.last_meal_time + philosopher.dinner->time_to_die)
	{
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			philosopher.dinner->n_dead++;
			printf("\033[31m%lld %3i died\033[0m\n",
				get_time(), philosopher.seat);
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		return (1);
	}
	return (0);
}
