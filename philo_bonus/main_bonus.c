/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:21:28 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/24 11:14:10 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int	verbose;

	verbose = 1;
	if (init_arguments(argc, argv, verbose))
		return (1);
	sem_t forks;
	
	
	printf("\n");
	return (0);
}
