/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:21:28 by abessa-m          #+#    #+#             */
/*   Updated: 2025/03/03 11:45:48 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_close_unlink(t_dinner *dinner);

//	struct s_dinner
//		int		verbose;
//		int		n_philosophers;
//		int		time_to_die;
//		int		time_to_eat;
//		int		time_to_zzz;
//		int		must_eat;
//		int		n_dead;
//		sem_t	*forks; -> numbers of pairs of forks
//		sem_t	*print;
//	struct s_philosopher
//		t_dinner	*dinner;
//		int			seat;
//		int			meals_eaten;
//		long long	last_meal_time;
int	main(int argc, char **argv)
{
	t_dinner		*dinner;
	int				verbose;

	verbose = 0;
	if (init_arguments(argc, argv, verbose))
		return (1);
	dinner = initialize_dinner(argc, argv, verbose);
	if (dinner == NULL)
		return (2);
	if (initialize_philosophers(dinner) != 0)
		return (printf("Philosophers error.\n"), free_close_unlink(dinner), 3);
	free_close_unlink(dinner);
	return (0);
}

void	free_close_unlink(t_dinner *dinner)
{
	sem_close(dinner->forks);
	sem_unlink("forks");
	sem_close(dinner->print);
	sem_unlink("print");
	usleep((dinner->time_to_die) * 1000);
	free(dinner);
}
