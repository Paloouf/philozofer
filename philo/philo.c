/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/15 16:39:06 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forquetta(t_philo *philo)
{
	if (philo->p_num % 2 == 0)
	{
		philo->fork_status = 1;
		pthread_mutex_lock(&philo->fork_l);
		status_message(philo, " has taken a fork 🍴");
		philo->fork_status = 2;
		pthread_mutex_lock(philo->fork_r);
	}
	if (philo->p_num % 2 == 1)
	{
		philo->fork_status = 1;
		pthread_mutex_lock(philo->fork_r);
		status_message(philo, " has taken a fork 🍴");
		philo->fork_status = 2;
		pthread_mutex_lock(&philo->fork_l);
	}
}

void	mangiaren(t_philo *philo)
{
	status_message(philo, " has taken a fork 🍴");
	status_message(philo, " is eating 🍝");
	pthread_mutex_lock(&philo->meat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meat_count);
}

void	mangiare(t_philo *philo)
{
	philo->eat_status = 1;
	take_forquetta(philo);
	mangiaren(philo);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_lock(&philo->info->mooteks);
	philo->time_since_eat = get_time();
	pthread_mutex_unlock(&philo->info->mooteks);
	status_message(philo, " is sleeping 💤");
	if (philo->p_num % 2 == 0)
	{
		if (philo->fork_status > 1)
			pthread_mutex_unlock(philo->fork_r);
		if (philo->fork_status > 0)
			pthread_mutex_unlock(&philo->fork_l);
	}
	else
	{
		if (philo->fork_status > 1)
			pthread_mutex_unlock(&philo->fork_l);
		if (philo->fork_status > 0)
			pthread_mutex_unlock(philo->fork_r);
	}
	ft_usleep(philo->info->time_to_sleep);
	philo->fork_status = 0;
	status_message(philo, " is thinking 🤔");
}

void	*loop(t_philo *philo)
{
	if (philo->p_num % 2 == 0)
		ft_usleep(philo->info->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->info->death);
		if (!*philo->is_dead)
		{
			pthread_mutex_unlock(&philo->info->death);
			mangiare(philo);
		}
		else
		{
			pthread_mutex_unlock(&philo->info->death);
			break ;
		}
	}
	return (NULL);
}
