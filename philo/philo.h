/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:00:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:58 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*	mandatory
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock,

**	shared
memset, printf, malloc, free, write,
pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday,

	bonus
fork, kill, exit,
waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink
*/

# include <pthread.h>	//pthread_mutex_init(), pthread_mutex_destroy(),
	//pthread_mutex_lock(), pthread_mutex_unlock(),
	//pthread_create(),
	//pthread_detach(),
	//pthread_join(),
# include <string.h>	//memset(),
# include <stdio.h>		//printf(),
# include <stdlib.h>	//malloc(), free(),
# include <unistd.h>	//write(),
	//usleep(),
# include <sys/time.h>	//gettimeofday(),

typedef struct s_dinner			t_dinner;
typedef struct s_philosopher	t_philosopher;

struct s_dinner
{
	int				verbose;
	int				n_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_zzz;
	int				must_eat;
	int				*fork_use;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
};

struct s_philosopher
{
	t_dinner	*dinner;
	int			seat;
	int			meals_eaten;
};

//	initialize.c
int				init_arguments(int argc, char **argv, int verbose);
t_dinner		*initialize_dinner(int argc, char **argv, int verbose);
t_philosopher	*initialize_philosophers(t_dinner	*dinner);
void			free_and_close(t_philosopher *philosophers, t_dinner *dinner);
//	utils.c
int				ft_atoi(const char *nptr);

#endif
