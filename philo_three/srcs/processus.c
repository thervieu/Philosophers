/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:09 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 15:23:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

void		*check_death(void *phi)
{
	t_philo *p;

	p = (t_philo*)phi;
	while (1 && *(p->env->someone_dead) == 0)
	{
		if (p->dead == 1)
			break ;
		sem_wait(p->check);
		if (get_time() > (p->time_last_eat + p->env->time_to_die))
		{
			p->dead = 1;
			print_msg(p, "died");
			sem_wait(p->env->write_sem);
			sem_post(p->check);
			free_env(p->env, -1);
			exit(0);
		}
		sem_post(p->check);
		ft_usleep(1000);
	}
	return (NULL);
}

int			death(t_philo *p)
{
	if (*(p->env->someone_dead) || p->nb_eat == p->env->nb_must_eat)
	{
		p->dead = 1;
		*(p->env->someone_dead) = 1;
		return (1);
	}
	return (0);
}

void		routine(t_philo *phi)
{
	t_philo		*p;

	p = (t_philo*)phi;
	p->time_last_eat = get_time();
	if (pthread_create(&(p->death), NULL, &check_death, phi) != 0)
		return ;
	while (1 && *(p->env->someone_dead) == 0)
	{
		if (p->dead)
			break ;
		eat(p);
		if (death(p) == 1)
			break ;
		print_msg(p, "is sleeping");
		ft_usleep(p->env->time_to_sleep * 1000);
		if (*(p->env->someone_dead))
			break ;
		print_msg(p, "is thinking");
		if (*(p->env->someone_dead))
			break ;
	}
	free_env(p->env, -1);
	exit(1);
	return ;
}

int			init_processus(t_env *env)
{
	int			i;

	i = -1;
	env->st = get_time();
	while (++i < env->nb_philo)
	{
		env->philos[i].pid = fork();
		if (env->philos[i].pid < 0)
			return (ERROR);
		else if (env->philos[i].pid == 0)
			routine(&(env->philos[i]));
		usleep(70);
	}
	return (SUCCESS);
}

int			wait_for_end(t_env *env)
{
	int				status;
	int				status_value;
	int				i;

	i = 0;
	while (i < env->nb_philo)
	{
		waitpid(-1, &status, 0);
		if ((WIFEXITED(status) || WIFSIGNALED(status)))
		{
			if ((status_value = WEXITSTATUS(status)) == 0)
			{
				while (i < env->nb_philo)
				{
					if (i != env->nb_philo)
						kill(env->philos[i].pid, SIGTERM);
					i++;
				}
				break ;
			}
			else if (status_value == 1)
				i++;
		}
	}
	return (0);
}
