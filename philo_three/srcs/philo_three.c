/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:24:43 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 01:43:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

static t_philo			*init_philos(t_env *env)
{
	int			nb;
	t_philo		*phi;
	char		str[256];

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
		new_name(CHECK, (char*)str, nb);
		if ((phi[nb].check = create_sem(CHECK, 1)) < 0)
			return (NULL);
		phi[nb].env = env;
	}
	return (phi);
}

static int				init_sem(t_env **env)
{
	if (((*env)->forks = create_sem(FORKS, (*env)->nb_philo)) < 0
		|| ((*env)->end = create_sem(END_SEM, 0)) < 0
		|| ((*env)->write_sem = create_sem(WRITE, 1)) < 0)
		return (ERROR);
	return (SUCCESS);
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
	if (init_sem(&env) == ERROR)
		return (NULL);
	if (init_sem(&env) == ERROR)
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
		free_env(env, -1);
	return (1);
}

int						main(int ac, char **av)
{
	t_env	*env;

	env = NULL;
	if (ac < 5 || ac > 6)
		return (print_clear(env, 0));
	if ((ac == 5 && (ft_atoi_pos(av[1]) < 0 || ft_atoi_pos(av[2]) < 0
		|| ft_atoi_pos(av[3]) < 0 || ft_atoi_pos(av[4]) < 0))
		|| (ac == 6 && (ft_atoi_pos(av[1]) < 0 || ft_atoi_pos(av[2]) < 0
		|| ft_atoi_pos(av[3]) < 0 || ft_atoi_pos(av[4]) < 0
		|| ft_atoi_pos(av[5]) < 0)))
		return (print_clear(env, 1));
	if (!(env = init_env(av)) || init_processus(env) == ERROR)
		return (print_clear(env, 2));
	sem_wait(env->end);
	while (--(env->nb_philo) >= 0)
		kill(env->philos[env->nb_philo].pid, SIGKILL);
	free_env(env, -1);
	return (0);
}
