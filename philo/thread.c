/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/20 17:21:08 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	struct s_philosopher
//		t_dinner	*dinner;
//		int			seat;
//		int			meals_eaten;
void	*philosopher_thread(void *arg)
{
	t_philosopher	philosopher;

	philosopher = *(t_philosopher *)arg;
	if (philosopher.dinner->verbose)
	{
		//usleep(philosopher.seat * 100 * 1000);
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		printf("\033[1;93mseat%3i:\033[0m  "
			"A wild philosopher appears!\n", philosopher.seat);
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	}
	philosopher.last_meal_time = get_time();
	while (philosopher.dinner->n_dead == 0)
	{
		//take left fork
		//am i already dead?
		//take right fork
		//am i already dead?
		//eat
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		printf("\033[32m%lld %3i is eating\033[0m\n",
			get_time(), philosopher.seat);
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		philosopher.meals_eaten++;
		if (philosopher.meals_eaten >= philosopher.dinner->must_eat)
			break ;
		usleep(philosopher.dinner->time_to_eat * 1000);
		//release the forks
		//sleep
			//am i already dead?
	}
	return (arg);
}
