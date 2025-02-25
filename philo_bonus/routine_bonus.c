/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:31:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/25 11:32:51 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosophize(t_philosopher *philosopher)
{
	//usleep (philosopher->seat * 100);
	while (1)
	{
		printf("A wild philosopher has appeared in seat %i\n", philosopher->seat);
		//take fork
		sem_wait(philosopher->dinner->forks);
		printf("%lld %d has takes a fork\n%lld %d has takes a fork\n",
			get_time(), philosopher->seat, get_time(), philosopher->seat);
			//am i dead
		//eat
		philosopher->last_meal_time = get_time();
		printf("%lld %d is eating\n", philosopher->last_meal_time, philosopher->seat);
		philosopher->meals_eaten++;
		usleep(philosopher->dinner->time_to_eat * 1000);
		//am i dead
		//dro-drop the forks
		sem_post(philosopher->dinner->forks);
		if (philosopher->meals_eaten > philosopher->dinner->must_eat)
			break ;
		//sleep
		printf("%lld %d is sleeping\n", get_time(), philosopher->seat);
		usleep(philosopher->dinner->time_to_zzz * 1000);
			//am i dead
		//think
		printf("%lld %d is thinking\n", get_time(), philosopher->seat);
	}
}
