/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/17 18:10:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	mandatory
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock,

	shared
memset, printf, malloc, free, write,
pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday,

	bonus
fork, kill, exit,
waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
*/
int	init_arguments(int argc, char **argv);

int	main(int argc, char **argv)
{
	if (init_arguments(argc, argv))
		return (1);
	printf("Let's think about it.\n");
	return (0);
}

int	init_arguments(int argc, char **argv)
{
	if (argc < (4 + 1))
	{
		printf("Too few arguments for %s\n", argv[0]);
		printf("Usage:	%s n_thinkers time_to_die time_to_eat time_to_sleep "
			"[upper_bound_to_eat]\n", argv[0]);
		return (1);
	}
	else if (argc > (5 + 1))
	{
		printf("Too many arguments for %s\n", argv[0]);
		printf("Usage:	%s n_thinkers time_to_die time_to_eat time_to_sleep "
			"[upper_bound_to_eat]\n", argv[0]);
		return (2);
	}
	return (0);
}

