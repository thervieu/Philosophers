/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:06:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->env->forks[p->left_fork]);
	print_msg(p, "has taken a fork");
	pthread_mutex_lock(&p->env->forks[p->right_fork]);
	print_msg(p, "has taken a fork");
}

void	give_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->env->forks[p->left_fork]);
	pthread_mutex_unlock(&p->env->forks[p->right_fork]);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->check);
	if (*(p->env->someone_dead) == 0)
	{
		p->time_last_eat = get_time();
		print_msg(p, "is eating");
		ft_usleep(p->env->time_to_eat * 1000);
		p->nb_eat++;
	}
	pthread_mutex_unlock(&p->check);
}
