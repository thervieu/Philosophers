/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 09:37:16 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 13:46:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

int			ft_atoi_pos(char *str)
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
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (nb);
}

int			free_env(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_philo)
	{
		pthread_mutex_destroy(&(env->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(env->write_mutex));
	if (env->philos)
		free(env->philos);
	if (env->forks)
		free(env->forks);
	if (env)
		free(env);
	return (1);
}
