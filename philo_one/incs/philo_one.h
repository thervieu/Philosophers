/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 18:05:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR 1
# define EAT 2
# define THINK 3
# define SLEEP 4
# define FORK 5
# define DIED 6
# define END 7

struct s_env;

typedef struct	s_philo
{
	int				id;
	int				nb_eat;
	int				eating;
	int				left_fork;
	int				right_fork;
	long long		time_last_eat;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	check;
	struct s_env	*env;
}				t_philo;

typedef struct	s_env
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long long		st;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end;
}				t_env;

/*
** actions.c
*/

void			take_forks(t_philo *p);

void			give_forks(t_philo *p);

void			eat(t_philo *philo);

/*
** threads.c
*/

int				init_threads(t_env *env);

/*
** precise_time.c
*/

long long		get_time(void);

void			ft_usleep(size_t wait_time);

/*
** utils.c
*/

int				ft_atoi_pos(char *str);

long long		get_time(void);

int				ft_atoi_pos(char *str);

int				free_env(t_env *env);

#endif
