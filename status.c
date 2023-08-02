/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:32:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/02 18:40:31 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_message(t_philo *philo, char *str)
{
	long	result;
	
	if (!philo->is_dead)
	{
		pthread_mutex_lock(&philo->info->print);
		result = get_time() - philo->info->start_time;
		printf("%ld ms %d %s", result, philo->p_num + 1, str);
		pthread_mutex_unlock(&philo->info->print);
	}
}	