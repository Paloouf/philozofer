/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/11 13:45:53 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rip_timer(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->info->is_deady);
		if (philo->is_dead)
		{
			sem_post(philo->info->is_deady);
			break ;
		}
		sem_post(philo->info->is_deady);
		sem_wait(philo->info->timer);
		if (get_time() - philo->time_since_eat > philo->info->time_to_die)
		{
			status_message(philo, "is kill 💀", 1);
			sem_post(philo->info->timer);
			break ;
		}
		sem_post(philo->info->timer);
	}
}

void	check_rip(t_philo *philo)
{
	sem_wait(philo->info->dead);
	sem_wait(philo->info->is_deady);
	philo->is_dead = 1;
	sem_post(philo->info->is_deady);
}

void	mangiare(t_philo *philo)
{
	sem_wait(philo->info->forks);
	status_message(philo, " has taken a forquetta 🍴", 0);
	sem_wait(philo->info->forks);
	status_message(philo, " has taken a forquetta 🍴", 0);
	status_message(philo, " is mangiaring 🍝", 0);
	philo->eat_count++;
	sem_wait(philo->info->timer);
	philo->time_since_eat = get_time();
	sem_post(philo->info->timer);
	if (philo->eat_count == philo->info->win_con)
		sem_post(philo->info->cwin);
	ft_usleep(philo->info->time_to_eat);
	status_message(philo, " is dodoing 💤", 0);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	ft_usleep(philo->info->time_to_sleep);
	status_message(philo, " is pensing 🤔", 0);
}

void	*loop(t_data *data, int i)
{
	if (i % 2 == 0)
		ft_usleep(data->time_to_eat / 10);
	pthread_create(&data->phil[i].rip, NULL, (void *)rip_timer, &data->phil[i]);
	pthread_create(&data->phil[i].rips, NULL,
		(void *)check_rip, &data->phil[i]);
	pthread_detach(data->phil[i].rip);
	pthread_detach(data->phil[i].rips);
	while (1)
	{
		sem_wait(data->is_deady);
		if (!data->phil[i].is_dead)
		{
			sem_post(data->is_deady);
			mangiare(&data->phil[i]);
		}
		else
		{
			sem_post(data->is_deady);
			break ;
		}
	}
	free(data->phil);
	exit(0);
}
