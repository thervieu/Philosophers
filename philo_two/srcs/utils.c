/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:16 by user42            #+#    #+#             */
/*   Updated: 2021/01/19 15:46:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_two.h"

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

	sem_unlink(FORKS);
	sem_unlink(END_SEM);
	sem_unlink(WRITE);
	if (env->philos)
	{
		i = 0;
		while (i < env->nb_philo)
		{
			new_name(CHECK, (char*)semaphore, i);
			sem_unlink(semaphore);
			new_name(EAT_SEM, (char*)semaphore, i);
			sem_unlink(semaphore);
			i++;
		}
		free(env->philos);
	}
	return (1);
}
