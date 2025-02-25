/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:58:52 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/25 09:21:29 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

t_dinner	*initialize_dinner(int argc, char **argv, int verbose)
{
	t_dinner	*dinner;

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
	dinner->n_dead = 0;
	dinner->forks = sem_open("forks", O_CREAT, 0644, (ft_atoi(argv[1]) / 2));
	//if (dinner->forks == SEM_FAILED)
	dinner->print = sem_open("print", O_CREAT, 0644, 1);
	//if (dinner->print == SEM_FAILED)
	return (dinner);
}
