/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 18:53:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

void		*check_count(void *envi)
{
	int		i;
	int		nb_eat;
	t_env	*env;

	nb_eat = 0;
	env = (t_env*)envi;
	while (nb_eat < env->nb_must_eat)
	{
		i = 0;
		while (i < env->nb_philo)
		{
			sem_wait(env->philos[i].eat_sem);
			i++;
		}
		nb_eat++;
	}
	sem_wait(env->write_sem);
	printf("All philosophers have eaten\n");
	sem_post(env->end);
	return ((void*)0);
}

void		*check_death(void *phi)
{
	t_philo *p;

	p = (t_philo*)phi;
	while (1)
	{
		sem_wait(p->check);
		if (!p->eating && get_time() > (p->time_last_eat + p->env->time_to_die))
		{
			sem_wait(p->env->write_sem);
			printf("%lld %d died\n", (get_time() - p->env->st)
				% 1000000, p->id + 1);
			sem_post(p->check);
			sem_post(p->env->end);
			return ((void*)0);
		}
		sem_post(p->check);
		ft_usleep(1000);
	}
}

void		*routine(void *phi)
{
	pthread_t	t_id;
	t_philo		*p;

	p = (t_philo*)phi;
	p->time_last_eat = get_time();
	if (pthread_create(&t_id, NULL, &check_death, phi) != 0)
		return (NULL);
	pthread_detach(t_id);
	while (1)
	{
		take_forks(p);
		eat(p);
		give_forks(p);
		sem_wait(p->env->write_sem);
		printf("%lld %d is thinking\n", (get_time() - p->env->st)
			% 1000000, p->id + 1);
		sem_post(p->env->write_sem);
	}
	return (NULL);
}

static int	init_nb_eat_count(t_env *env)
{
	pthread_t	t_id;

	if (env->nb_must_eat > 0)
	{
		if (pthread_create(&t_id, NULL, &check_count, (void*)env) != 0)
			return (ERROR);
		pthread_detach(t_id);
	}
	return (SUCCESS);
}

int			init_processus(t_env *env)
{
	int			i;
	void		*philo;

	i = -1;
	if (init_nb_eat_count(env) == ERROR)
		return (ERROR);
	env->st = get_time();
	while (++i < env->nb_philo)
	{
		philo = (void*)(&env->philos[i]);
		env->philos[i].pid = fork();
		if (env->philos[i].pid < 0)
			return (ERROR);
		else if (env->philos[i].pid == 0)
		{
			routine(&env->philos[i]);
			exit(0);
		}
		usleep(70);
	}
	return (SUCCESS);
}
