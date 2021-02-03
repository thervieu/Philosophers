/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:16 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 15:14:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_three.h"

int		ft_atoi_pos(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		++i;
	}
	if (str[i] != '\0')
		return (-1);
	return (nb);
}

int		ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

int		free_env(t_env *env)
{
	int		i;
	char	semaphore[255];

	sem_close(env->forks);
	sem_close(env->write_sem);
	sem_close(env->end);
	sem_unlink(FORKS);
	sem_unlink(END_SEM);
	sem_unlink(WRITE);
	if (env->philos)
	{
		i = -1;
		while (++i < env->nb_philo)
		{
			new_name(CHECK, (char*)semaphore, i);
			sem_close(env->philos[i].check);
			sem_unlink(semaphore);
		}
	}
	(env->philos) ? free(env->philos) : 0;
	(env->someone_dead) ? free(env->someone_dead) : 0;
	(env) ? free(env) : 0;
	return (1);
}

void	print_msg(t_philo *p, char *s)
{
	if (*(p->env->someone_dead) == 1 && p->dead == 0)
		return ;
	else if (p->dead)
		p->dead = 0;
	sem_wait(p->env->write_sem);
	printf("%lld %d ", (get_time() - p->env->st) % 1000000, p->id + 1);
	printf("%s\n", s);
	sem_post(p->env->write_sem);
	return ;
}
