/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/19 12:02:26 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	mandatory		Each philosopher should be a thread!
pthread_mutex_init,
pthread_mutex_destroy
pthread_mutex_lock,
pthread_mutex_unlock,

	shared
memset, printf, malloc, free, write,
pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday,
*/

int	main(int argc, char **argv)
{
	t_dinner		*dinner;
	t_philosopher	*philosophers;
	int				verbose;
	//pthread_t		*threads;
	//int				i;

	verbose = 1;
	if (init_arguments(argc, argv, verbose))
		return (1);
	dinner = initialize_dinner(argc, argv, verbose);
	if (dinner == NULL)
		return (2);
	philosophers = initialize_philosophers(dinner);
	//if (philosophers == NULL)
	//	return (free_and_close(NULL, &dinner), 3);
	//i = 0;
	//while (i < &dinner->n_philosophers)
	//{
	//	pthread_create(&threads[i], NULL, philosopher_thread, &philosophers[i])
	//	i++;
	//}
	//i = 0;
	//while (i < &dinner->n_philosophers)
	//	pthread_join(&threads[i++], NULL);
	return (free_and_close(philosophers, dinner), 0);
}
