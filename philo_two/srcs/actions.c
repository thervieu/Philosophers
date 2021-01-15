/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 18:16:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

void	take_forks(t_philo *p)
{
	sem_wait(p->env->forks);
	sem_wait(p->env->write_sem);
	printf("%lld %d has taken a fork\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	sem_post(p->env->write_sem);
	sem_wait(p->env->forks);
	sem_wait(p->env->write_sem);
	printf("%lld %d has taken a fork\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	sem_post(p->env->write_sem);
}

void	give_forks(t_philo *p)
{
	sem_post(p->env->forks);
	sem_post(p->env->forks);
	sem_wait(p->env->write_sem);
	printf("%lld %d is sleeping\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	sem_post(p->env->write_sem);
	ft_usleep(p->env->time_to_sleep * 1000);
}

void	eat(t_philo *p)
{
	sem_wait(p->check);
	p->eating = 1;
	sem_wait(p->env->write_sem);
	printf("%lld %d is eating\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	sem_post(p->env->write_sem);
	p->time_last_eat = get_time();
	ft_usleep(p->env->time_to_eat * 1000);
	p->nb_eat++;
	p->eating = 0;
	sem_post(p->check);
	sem_post(p->eat_sem);
}
