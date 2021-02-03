/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:07:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define SUCCESS 0
# define ERROR 1
# define EAT 2
# define THINK 3
# define SLEEP 4
# define FORK 5
# define DIED 6
# define END 7

# define CHECK "/check_sema"
# define EAT_SEM "/eat_sema"

# define FORKS "/forks"
# define END_SEM "/end"
# define WRITE "/write"

struct s_env;

typedef struct	s_philo
{
	int				id;
	int				nb_eat;
	int				dead;
	pthread_t		death;
	pthread_t		routine;
	int				left_fork;
	int				right_fork;
	long long		time_last_eat;
	sem_t			*check;
	struct s_env	*env;
}				t_philo;

typedef struct	s_env
{
	int				nb_philo;
	int				*someone_dead;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	long long		st;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write_sem;
	sem_t			*end;
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

int				init_threads(t_env *env, int i);

/*
** time_and_sem.c
*/

long long		get_time(void);

char			*new_name(char const *base, char *buffer, int position);

sem_t			*create_sem(char *name, int value);

void			ft_usleep(size_t wait_time);

/*
** utils.c
*/

int				ft_atoi_pos(char *str);

int				free_env(t_env *env, int i);

int				ft_strcpy(char *dst, const char *src);

void			print_msg(t_philo *p, char *s);

#endif
