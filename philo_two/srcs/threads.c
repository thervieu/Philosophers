/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 16:27:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

void	*check_count(void *envi)
{
	int		i;
	int		nb_eat;
	t_env	*env;

	nb_eat = -1;
	env = (t_env*)envi;
	while (++nb_eat < env->nb_must_eat)
	{
		i = -1;
		while (++i < env->nb_philo)
			sem_wait(env->philos[i].eat_sem);
	}
	sem_wait(env->write_sem);
	sem_post(env->end);
	return ((void*)0);
}

void	*check_death(void *phi)
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

void	*routine(void *phi)
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

int		init_threads(t_env *env)
{
	int			i;
	pthread_t	t_id;
	void		*philo;

	i = 0;
	if (env->nb_must_eat > 0)
	{
		if (pthread_create(&t_id, NULL, &check_count, (void*)env) != 0)
			return (1);
		pthread_detach(t_id);
	}
	env->st = get_time();
	while (i < env->nb_philo)
	{
		philo = (t_philo*)(&env->philos[i]);
		if (pthread_create(&t_id, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(t_id);
		usleep(70);
		i++;
	}
	return (0);
}
