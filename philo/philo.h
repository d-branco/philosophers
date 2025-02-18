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

#endif