/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:32:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/31 16:21:59 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_message(t_data *data, int i)
{
	struct timeval	time;
	long	result;

	gettimeofday(&time, NULL);
	result = (time.tv_sec * 1000 + time.tv_usec / 1000) - data->start_time;
	if (data->phil[i].fork_status)
	{
		printf("%ld ms %d has taken a fork\n", result, data->phil[i].p_num);
		printf("%ld ms %d has taken a fork\n", result, data->phil[i].p_num);
	}
	else if (data->phil[i].eat_status)
		printf("%ld ms %d is eating\n", result, data->phil[i].p_num);
	else if (data->phil[i].sleep_status)
		printf("%ld ms %d is sleeping\n", result, data->phil[i].p_num);
	else if (data->phil[i].think_status)
		printf("%ld ms %d is thinking\n", result, data->phil[i].p_num);
	else if (data->phil[i].is_dead)
		printf("%ld ms %d died\n", result, data->phil[i].p_num);
}