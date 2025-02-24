/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:21:59 by abessa-m          #+#    #+#             */
/*   Updated: 2025/02/24 11:50:34 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

# include <pthread.h>
	//pthread_create(), pthread_detach(), pthread_join(),
# include <string.h>	//memset(),
# include <stdio.h>		//printf(),
# include <stdlib.h>	//malloc(), free(),
	//exit(), 
# include <unistd.h>	//write(),
	//usleep(),
	//fork(), 
# include <sys/time.h>	//gettimeofday(),
# include <signal.h>	//kill(), 
# include <sys/wait.h>	//waitpid(), 
//#include <fcntl.h>	/* For O_* constants */
//#include <sys/stat.h>	/* For mode constants */
# include <semaphore.h>
	//sem_open(), sem_close(), sem_post(), sem_wait(), sem_unlink(), 

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
	int				n_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
};

struct s_philosopher
{
	t_dinner	*dinner;
	int			seat;
	int			meals_eaten;
	long long	last_meal_time;
};

//	initialize_bonus.c
int			init_arguments(int argc, char **argv, int verbose);
//	utils_bonus.c
long long	get_time(void);
int			ft_atoi(const char *nptr);

#endif