/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/03/03 14:11:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	struct s_philosopher
//		t_dinner	*dinner;
//		int			seat;
//		int			meals_eaten;
//		long long	last_meal_time;
void	*philosopher_thread(void *arg)
{
	t_philosopher	philosopher;
	int				enter_loop;
	int				first_fork;
	int				second_fork;

	philosopher = *(t_philosopher *)arg;
	usleep((philosopher.seat % 2) * 2 * 1000);
	enter_loop = 1;
	first_fork = place_first_fork(&philosopher);
	second_fork = place_second_fork(&philosopher);
	pthread_mutex_lock(&philosopher.dinner->print_mutex);
	if (!philosopher.dinner->n_dead)
		take_a_seat(&philosopher, first_fork, second_fork);
	else
		enter_loop = 0;
	pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	philosopher.last_meal_time = get_time();
	if (enter_loop)
		enter_loop = multi_philosopher_case(&philosopher);
	if (enter_loop)
		philosophize_or_die_trying(&philosopher, first_fork, second_fork);
	return (arg);
}

void	take_a_seat(t_philosopher *philosopher, int f1, int f2)
{
	if (philosopher->dinner->verbose)
	{
		printf("\033[1;93mseat%3i:\033[0m  "
			"A wild philosopher appears!\n", philosopher->seat);
		printf("\033[1;93mseat%3i:\033[0m  takes forks:%4i, and%4i\n",
			philosopher->seat, f1, f2);
	}
}

int	multi_philosopher_case(t_philosopher *philosopher)
{
	if (philosopher->dinner->n_philosophers == 1)
	{
		pthread_mutex_lock(&philosopher->dinner->print_mutex);
		printf("\033[35m%lld %3i has taken a fork\033[0m\n",
			get_time(), philosopher->seat);
		usleep((philosopher->dinner->time_to_die + 1) * 1000);
		printf("\033[31m%lld %3i died",
			get_time(), philosopher->seat);
		if (philosopher->dinner->verbose)
			printf("%4lld miliseconds ago!",
				get_time() - philosopher->last_meal_time
				- philosopher->dinner->time_to_die);
		printf("\033[0m\n");
		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
		return (0);
	}
	else if ((philosopher->dinner->time_to_die - 3
			<= ((2 + (philosopher->dinner->n_philosophers % 2))
				* philosopher->dinner->time_to_eat))
		&& (philosopher->dinner->n_philosophers == philosopher->seat))
		return (usleep(1000 * (philosopher->dinner->time_to_die - get_time() + 1
					+ philosopher->last_meal_time)),
			am_i_already_dead(philosopher), 0);
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
		pthread_mutex_lock(&philosopher->dinner->print_mutex);
		if (!philosopher->dinner->n_dead)
		{
			philosopher->dinner->n_dead++;
			printf("\033[31m%lld %3i died",
				time_of_death, philosopher->seat);
			if (philosopher->dinner->verbose)
				printf("%4lld miliseconds ago!", time_of_death
					- philosopher->last_meal_time
					- philosopher->dinner->time_to_die);
			printf("\033[0m\n");
		}
		pthread_mutex_unlock(&philosopher->dinner->print_mutex);
		return (1);
	}
	return (0);
}
