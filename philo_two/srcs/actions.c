/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:25:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:06:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

void	take_forks(t_philo *p)
{
	sem_wait(p->env->forks);
	print_msg(p, "has taken a fork");
	sem_wait(p->env->forks);
	print_msg(p, "has taken a fork");
}

void	give_forks(t_philo *p)
{
	sem_post(p->env->forks);
	sem_post(p->env->forks);
}

void	eat(t_philo *p)
{
	sem_wait(p->check);
	if (*(p->env->someone_dead) == 0)
	{
		p->time_last_eat = get_time();
		print_msg(p, "is eating");
		ft_usleep(p->env->time_to_eat * 1000);
		p->nb_eat++;
	}
	sem_post(p->check);
}
