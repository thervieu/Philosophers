/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 15:53:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->env->forks[p->left_fork]);
	pthread_mutex_lock(&p->env->write_mutex);
	printf("%lld %d has taken a fork\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	pthread_mutex_unlock(&p->env->write_mutex);
	pthread_mutex_lock(&p->env->forks[p->right_fork]);
	pthread_mutex_lock(&p->env->write_mutex);
	printf("%lld %d has taken a fork\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	pthread_mutex_unlock(&p->env->write_mutex);
}

void	give_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->env->forks[p->left_fork]);
	pthread_mutex_unlock(&p->env->forks[p->right_fork]);
	pthread_mutex_lock(&p->env->write_mutex);
	printf("%lld %d is sleeping\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	pthread_mutex_unlock(&p->env->write_mutex);
	ft_usleep(p->env->time_to_sleep * 1000);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->check);
	p->eating = 1;
	p->time_last_eat = get_time();
	pthread_mutex_lock(&p->env->write_mutex);
	printf("%lld %d is eating\n", (get_time() - p->env->st)
		% 1000000, p->id + 1);
	pthread_mutex_unlock(&p->env->write_mutex);
	ft_usleep(p->env->time_to_eat * 1000);
	p->nb_eat++;
	p->eating = 0;
	pthread_mutex_unlock(&p->check);
	pthread_mutex_unlock(&p->eat_mutex);
}
