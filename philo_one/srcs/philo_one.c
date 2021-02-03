/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:24:43 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:08:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

static t_philo			*init_philos(t_env *env)
{
	int			nb;
	t_philo		*phi;

	nb = -1;
	if (!(phi = malloc(sizeof(t_philo) * env->nb_philo)))
		return (NULL);
	while (++nb < env->nb_philo)
	{
		phi[nb].id = nb;
		phi[nb].dead = 0;
		phi[nb].nb_eat = 0;
		phi[nb].left_fork = nb;
		phi[nb].right_fork = (nb + 1) % env->nb_philo;
		phi[nb].time_last_eat = get_time();
		pthread_mutex_init(&(phi[nb].check), NULL);
		phi[nb].env = env;
	}
	return (phi);
}

static pthread_mutex_t	*init_forks(t_env *env)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	if (!(forks = malloc(sizeof(pthread_mutex_t) * env->nb_philo)))
		return (NULL);
	while (++i < env->nb_philo)
	{
		pthread_mutex_init(&(forks[i]), NULL);
	}
	return (forks);
}

static t_env			*init_env(char **av)
{
	t_env	*env;

	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	memset(env, 0, sizeof(t_env));
	if (!(env->someone_dead = malloc(sizeof(int))))
		return (NULL);
	*(env->someone_dead) = 0;
	env->nb_philo = ft_atoi_pos(av[1]);
	env->time_to_die = ft_atoi_pos(av[2]);
	env->time_to_eat = ft_atoi_pos(av[3]);
	env->time_to_sleep = ft_atoi_pos(av[4]);
	env->nb_must_eat = (av[5]) ? ft_atoi_pos(av[5]) : -2;
	if (env->nb_philo < 0 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->nb_must_eat == -1)
		return (NULL);
	pthread_mutex_init(&(env->write_mutex), NULL);
	pthread_mutex_init(&(env->end), NULL);
	pthread_mutex_lock(&(env->end));
	if (!(env->forks = init_forks(env)))
		return (NULL);
	if (!(env->philos = init_philos(env)))
		return (NULL);
	return (env);
}

static int				print_clear(t_env *env, int i)
{
	if (i == 0)
	{
		printf("Error: philo_two: format: ./philo_two [nb_philosophers] ");
		printf("[time_to_die] [time_to_eat] [time_to_sleep] ");
		printf("([nb_time_each_philo_must_eat])\n");
	}
	else if (i == 1)
		printf("Error: philo_two: wrong argument\n");
	else if (i == 2)
		printf("Error: philo_two: fatal error\n");
	if (env)
		free_env(env);
	return (1);
}

int						main(int ac, char **av)
{
	t_env	*env;
	int		i;

	i = 0;
	env = NULL;
	if (ac < 5 || ac > 6)
		return (print_clear(env, 0));
	if (ac == 5 && (ft_atoi_pos(av[1]) < 0 || ft_atoi_pos(av[2]) < 0
		|| ft_atoi_pos(av[3]) < 0 || ft_atoi_pos(av[4]) < 0))
		return (print_clear(env, 1));
	if (ac == 6 && (ft_atoi_pos(av[1]) < 0 || ft_atoi_pos(av[2]) < 0
		|| ft_atoi_pos(av[3]) < 0 || ft_atoi_pos(av[4]) < 0
		|| ft_atoi_pos(av[5]) < 0))
		return (print_clear(env, 1));
	if (!(env = init_env(av)) || init_threads(env, 0) == ERROR)
		return (print_clear(env, 2));
	pthread_mutex_lock(&env->end);
	pthread_mutex_unlock(&env->end);
	while (i < env->nb_philo)
		pthread_join(env->philos[i++].death, NULL);
	i = 0;
	while (i < env->nb_philo)
		pthread_join(env->philos[i++].routine, NULL);
	free_env(env);
	return (0);
}
