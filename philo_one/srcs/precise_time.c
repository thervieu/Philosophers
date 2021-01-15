/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:25:15 by user42            #+#    #+#             */
/*   Updated: 2021/01/15 18:01:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo_one.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		ft_usleep(size_t wait_time)
{
	struct timeval	time1;
	struct timeval	time2;

	gettimeofday(&time1, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&time2, NULL);
		if ((size_t)(((size_t)(time2.tv_sec - time1.tv_sec) * 1000000)
			+ (size_t)(time2.tv_usec - time1.tv_usec)) > wait_time)
			break ;
	}
}
