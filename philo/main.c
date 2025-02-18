/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/18 20:49:17 by abessa-m         ###   ########.fr       */
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
	t_info	*info;
	int		verbose;

	verbose = 1;
	if (init_arguments(argc, argv, verbose))
		return (1);
	info = initialize_dinner(argc, argv, verbose);
	if (info == NULL)
		return (2);
	return (0);
}
