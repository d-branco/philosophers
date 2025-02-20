/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:04:45 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/20 16:03:55 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arguments(int argc, char **argv, int verbose)
{
	if (argc < (4 + 1))
	{
		printf("Too few arguments for %s\nUsage:	%s n_thinkers time_to_die t"
			"ime_to_eat time_to_sleep [max_meals_to_eat]\n", argv[0], argv[0]);
		return (1);
	}
	else if (argc > (5 + 1))
	{
		printf("Too many arguments for %s\n", argv[0]);
		printf("Usage:	%s n_thinkers time_to_die time_to_eat time_to_sleep "
			"[upper_bound_to_eat]\n", argv[0]);
		return (2);
	}
	else if (verbose)
	{
		printf("\033[1;93mINIT:\033[0m%4i	number of philosophers\n\033[1;93mI"
			"NIT:\033[0m%4i	miliseconds it takes to die\n\033[1;93mINIT:\033[0m"
			"%4i	miliseconds it takes to eat\n\033[1;93mINIT:\033[0m%4i	mil"
			"iseconds it takes to sleep\n", ft_atoi(argv[1]), ft_atoi(argv[2]),
			ft_atoi(argv[3]), ft_atoi(argv[4]));
		if (argc == (5 + 1))
			printf("\033[1;93mINIT:\033[0m%4i	number of times each philosophe"
				"r must eat\n", ft_atoi(argv[5]));
	}
	return (0);
}

//	struct s_dinner
//		int		verbose;
//		int			n_philosophers;
//		int			time_to_die;
//		int			time_to_eat;
//		int			time_to_zzz;
//		int				must_eat;
//		pthread_mutex_t		*forks;
//		pthread_mutex_t		print_mutex;
t_dinner	*initialize_dinner(int argc, char **argv, int verbose)
{
	t_dinner	*dinner;
	int			i;

	dinner = (t_dinner *)malloc(sizeof(t_dinner));
	if (dinner == NULL)
		return (NULL);
	dinner->verbose = verbose;
	dinner->n_philosophers = ft_atoi(argv[1]);
	dinner->time_to_die = ft_atoi(argv[2]);
	dinner->time_to_eat = ft_atoi(argv[3]);
	dinner->time_to_zzz = ft_atoi(argv[4]);
	dinner->must_eat = 2147483647;
	if (argc == 5 + 1)
		dinner->must_eat = ft_atoi(argv[5]);
	dinner->forks = malloc(dinner->n_philosophers * sizeof(pthread_mutex_t));
	if (dinner->forks == NULL)
		return (free_and_close(NULL, dinner), NULL);
	i = 0;
	while (i < dinner->n_philosophers)
		if (pthread_mutex_init(&dinner->forks[i++], NULL) != 0)
			return (free_and_close(NULL, dinner), NULL);
	if (pthread_mutex_init(&dinner->print_mutex, NULL) != 0)
		return (free_and_close(NULL, dinner), NULL);
	return (dinner);
}

//	struct s_philosopher
//		t_dinner	*dinner;
//		int			seat;
//		int			meals_eaten;
t_philosopher	*initialize_philosophers(t_dinner	*dinner)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = malloc(dinner->n_philosophers * sizeof(t_philosopher));
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < dinner->n_philosophers)
	{
		philosophers[i].dinner = dinner;
		philosophers[i].seat = i + 1;
		philosophers[i].meals_eaten = 0;
		i++;
	}
	return (philosophers);
}

pthread_t	*initialize_threads(t_dinner *dinner, t_philosopher *philosophers)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(dinner->n_philosophers * sizeof(pthread_t));
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < dinner->n_philosophers)
	{
		if (pthread_create(&threads[i], NULL,
				philosopher_thread, &philosophers[i]) != 0)
			return (free(threads), NULL);
		i++;
	}
	return (threads);
}

void	free_and_close(t_philosopher *philosophers, t_dinner *dinner)
{
	int	i;

	if (philosophers != NULL)
		free(philosophers);
	if (dinner != NULL)
	{
		if (dinner->forks != NULL)
		{
			i = 0;
			while (i < dinner->n_philosophers)
			{
				pthread_mutex_destroy(&dinner->forks[i]);
				i++;
			}
			free(dinner->forks);
		}
		pthread_mutex_destroy(&dinner->print_mutex);
		free(dinner);
	}
}
