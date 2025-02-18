/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/18 14:32:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	mandatory		Each philosopher should be a thread!
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock,

	shared
memset, printf, malloc, free, write,
pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday,
*/
int	init_arguments(int argc, char **argv);
int	ft_atoi(const char *nptr);

void	*routine(void *ptr)
{
	printf("Test from a thread!\n");
	usleep(3 * 1000 * 1000);
	printf("Ending thread\n");
	return (ptr);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (init_arguments(argc, argv))
		return (1);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (2);
	if (pthread_join(t2, NULL) != 0)
		return (2);
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
	printf("\033[1;93mINIT:\033[0m%4i	number of philosophers\n"
		"\033[1;93mINIT:\033[0m%4i	miliseconds it takes to die\n"
		"\033[1;93mINIT:\033[0m%4i	miliseconds it takes to eat\n"
		"\033[1;93mINIT:\033[0m%4i	miliseconds it takes to sleep\n",
		ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]), ft_atoi(argv[4]));
	if (argc == (5 + 1))
		printf("\033[1;93mINIT:\033[0m%4i	number of times each philosopher "
			"must eat\n", ft_atoi(argv[5]));
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sign;
	int	j;

	j = 0;
	while (nptr[j] == 32
		|| (nptr[j] >= 9 && nptr[j] <= 13))
		j++;
	sign = 1;
	if (nptr[j] == '+' || nptr[j] == '-')
	{
		if (nptr[j] == '-')
			sign = -1;
		j++;
	}
	nbr = 0;
	while ((nptr[j] >= '0') && (nptr[j] <= '9'))
	{
		nbr = (10 * nbr) + (nptr[j] - '0');
		j++;
	}
	nbr *= sign;
	return (nbr);
}
