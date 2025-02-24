/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:58:52 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/24 10:01:39 by abessa-m         ###   ########.fr       */
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
