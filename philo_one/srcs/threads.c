/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 13:46:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	*check_death(void *phi)
{
	t_philo *p;

	p = (t_philo*)phi;
	while (1 && *(p->env->someone_dead) == 0)
	{
		pthread_mutex_lock(&p->check);
		if (get_time() > (p->time_last_eat + p->env->time_to_die))
		{
			if (*(p->env->someone_dead) != 1)
			{
				p->dead = 1;
				*(p->env->someone_dead) = 1;
				if (p->nb_eat != p->env->nb_must_eat)
					print_msg(p, "died");
				pthread_mutex_unlock(&p->check);
				pthread_mutex_unlock(&(p->env->end));
				break ;
			}
		}
		pthread_mutex_unlock(&p->check);
		ft_usleep(1000);
	}
	return (NULL);
}

void	*routine(void *phi)
{
	t_philo		*p;

	p = (t_philo*)phi;
	p->time_last_eat = get_time();
	if (pthread_create(&(p->death), NULL, &check_death, phi) != 0)
		return (NULL);
	while (1 && *(p->env->someone_dead) == 0)
	{
		if (*(p->env->someone_dead))
			break ;
		take_forks(p);
		eat(p);
		give_forks(p);
		if (*(p->env->someone_dead) || p->nb_eat == p->env->nb_must_eat)
			break ;
		print_msg(p, "is sleeping");
		ft_usleep(p->env->time_to_sleep * 1000);
		if (*(p->env->someone_dead))
			break ;
		print_msg(p, "is thinking");
		if (*(p->env->someone_dead))
			break ;
	}
	return (NULL);
}

int		init_threads(t_env *env, int i)
{
	void		*p;

	env->st = get_time();
	while (i < env->nb_philo)
	{
		p = (t_philo*)(&env->philos[i]);
		if (pthread_create(&(env->philos[i].routine), NULL, &routine, p) != 0)
			return (1);
		usleep(70);
		i += 2;
	}
	ft_usleep(500);
	i = 1;
	while (i < env->nb_philo)
	{
		p = (t_philo*)(&env->philos[i]);
		if (pthread_create(&(env->philos[i].routine), NULL, &routine, p) != 0)
			return (1);
		usleep(70);
		i += 2;
	}
	return (0);
}
