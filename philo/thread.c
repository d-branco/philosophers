/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/21 15:20:06 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		am_i_already_dead(t_philosopher philosopher);
void	will_i_be_dead(t_philosopher philosopher, long long time_it_takes);
int		single_philosopher_case(t_philosopher philosopher);

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
	int				first_fork;
	int				second_fork;

	philosopher = *(t_philosopher *)arg;
	first_fork = (philosopher.seat - 1) + ((philosopher.seat - 1) % 2);//forks
	if (first_fork >= philosopher.dinner->n_philosophers)
		first_fork = 0;
	second_fork = ((philosopher.seat - 1) + 1) - ((philosopher.seat - 1) % 2);
	if (second_fork >= philosopher.dinner->n_philosophers)
		second_fork = 0;
	usleep(philosopher.seat * 1000);
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
					philosopher.seat, first_fork, second_fork);
			}
		}
		else
			enter_loop = 0;
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	}
	philosopher.last_meal_time = get_time();
	// only one
	enter_loop = single_philosopher_case(philosopher);
	while (enter_loop)
	{
		pthread_mutex_lock(&philosopher.dinner->forks[first_fork]);//take fork1
		if (am_i_already_dead(philosopher))
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork]);
			break ;
		}
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[35m%lld %3i has taken a fork\033[0m",
				get_time(), philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[35m%4i\033[0m", first_fork);
			printf("\n");
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		pthread_mutex_lock(&philosopher.dinner->forks[second_fork]);//take fork2
		if (am_i_already_dead(philosopher))
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork]);
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork]);
			break ;
		}
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			printf("\033[35m%lld %3i has taken a fork\033[0m",
				get_time(), philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[35m%4i\033[0m", second_fork);
			printf("\n");
		}
		philosopher.last_meal_time = get_time();
		if (!philosopher.dinner->n_dead) //eat
		{
			printf("\033[32m%lld %3i is eating\033[0m",
				philosopher.last_meal_time, philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("\033[32m meal %i\033[0m",
					(philosopher.meals_eaten + 1));
			printf("\n");
		}
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork]);
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork]);
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		philosopher.meals_eaten++;
		if (philosopher.meals_eaten >= philosopher.dinner->must_eat)
		{
			pthread_mutex_unlock(&philosopher.dinner->forks[first_fork]);
			pthread_mutex_unlock(&philosopher.dinner->forks[second_fork]);
			break ;
		}
		will_i_be_dead(philosopher, philosopher.dinner->time_to_eat);
		pthread_mutex_unlock(&philosopher.dinner->forks[first_fork]);//fork down
		pthread_mutex_unlock(&philosopher.dinner->forks[second_fork]);//forkdown
		if (am_i_already_dead(philosopher))
			break ;
		pthread_mutex_lock(&philosopher.dinner->print_mutex);//sleep
		if (!philosopher.dinner->n_dead)
			printf("\033[34m%lld %3i is sleeping\033[0m\n",
				get_time(), philosopher.seat);
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		will_i_be_dead(philosopher, philosopher.dinner->time_to_zzz);
		if (am_i_already_dead(philosopher))
			break ;
		pthread_mutex_lock(&philosopher.dinner->print_mutex);//think
		if (!philosopher.dinner->n_dead)
			printf("\033[36m%lld %3i is thinking\033[0m\n",
				get_time(), philosopher.seat);
		else
		{
			pthread_mutex_unlock(&philosopher.dinner->print_mutex);
			break ;
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
	}
	return (arg);
}

int	single_philosopher_case(t_philosopher philosopher)
{
	if (philosopher.dinner->n_philosophers == 1)
	{
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		printf("\033[35m%lld %3i has taken a fork\033[0m\n",
			get_time(), philosopher.seat);
		usleep(philosopher.dinner->time_to_die * 1000);
		printf("\033[31m%lld %3i died",
			get_time(), philosopher.seat);
		if (philosopher.dinner->verbose)
			printf("%4lld miliseconds ago!",
				get_time() - philosopher.last_meal_time
				- philosopher.dinner->time_to_die);
		printf("\033[0m\n");
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		return (0);
	}
	return (1);
}

void	will_i_be_dead(t_philosopher philosopher, long long time_it_takes)
{
	if (time_it_takes + get_time() > philosopher.last_meal_time
		+ philosopher.dinner->time_to_die)
		usleep(time_it_takes + get_time() - philosopher.last_meal_time
			- philosopher.dinner->time_to_die);
	else
		usleep(time_it_takes * 1000);
}

int	am_i_already_dead(t_philosopher philosopher)
{
	long long	time_of_death;

	time_of_death = get_time();
	if (time_of_death
		> philosopher.last_meal_time + philosopher.dinner->time_to_die)
	{
		pthread_mutex_lock(&philosopher.dinner->print_mutex);
		if (!philosopher.dinner->n_dead)
		{
			philosopher.dinner->n_dead++;
			//printf("\033[31m%lld %3i died\033[0m",
			//	philosopher.last_meal_time + philosopher.dinner->time_to_die,
			//	philosopher.seat);
			printf("\033[31m%lld %3i died",
				time_of_death, philosopher.seat);
			if (philosopher.dinner->verbose)
				printf("%4lld miliseconds ago!", time_of_death
					- philosopher.last_meal_time
					- philosopher.dinner->time_to_die);
			printf("\033[0m\n");
		}
		pthread_mutex_unlock(&philosopher.dinner->print_mutex);
		return (1);
	}
	return (0);
}
