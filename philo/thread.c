/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/20 19:22:55 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	//int				first_fork_position;// i for pair; i + 1 for odd
	//int				second_fork_position;//i for odd; i + 1 for pair

	enter_loop = 1;
	philosopher = *(t_philosopher *)arg;
	if (philosopher.dinner->verbose)
	{
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
			printf("\033[1;93mseat%3i:\033[0m  "
				"A wild philosopher appears!\n", philosopher.seat);
		else
			enter_loop = 0;
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	}
	//usleep(100 * 1000);//
	philosopher.last_meal_time = get_time();
	// if time_to_die < time_to_zz!
	//while (!philosopher.dinner->n_dead)
	while (enter_loop)
	{
		//take left fork
			//am i already dead?
		//take right fork
			//am i already dead?
		//eat
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
			printf("\033[32m%lld %3i is eating\033[0m\n",
				get_time(), philosopher.seat);
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		philosopher.meals_eaten++;
		if (philosopher.meals_eaten >= philosopher.dinner->must_eat)
			break ;
		usleep(philosopher.dinner->time_to_eat * 1000);
		philosopher.last_meal_time = get_time();
		//release the forks
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
			break ;
		}
	}
	return (arg);
}
