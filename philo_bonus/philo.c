/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:59:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/10 16:35:44 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rip_timer(t_philo *philo)
{
	while (1)
	{	
		sem_wait(philo->info->dead);
		if (philo->is_dead)
			break;
		if (get_time() - philo->time_since_eat > philo->info->time_to_die)
		{	
			
			philo->info->all_deads = 1;
			//printf("%p\n", &philo->info->all_deads);
			status_message(philo, "is kill 💀", 1);
			sem_post(philo->info->dead);
			break;
		}
		sem_post(philo->info->dead);
	}
}

// void	check_rip(t_philo *philo)
// {
// 	sem_wait(philo->info->dead);
// 	philo->is_dead = 1;
// 	sem_post(philo->info->dead);
// 	sem_post(philo->info->ok);
// }

void	mangiare(t_philo *philo)
{
	philo->check = 0;
	sem_wait(philo->info->forks);
	status_message(philo, " has taken a forquetta 🍴", 0);
	sem_wait(philo->info->forks);
	status_message(philo, " has taken a forquetta 🍴", 0);
	status_message(philo, " is mangiaring 🍝", 0);
	philo->eat_count++;
	philo->time_since_eat = get_time();
	if (philo->eat_count == philo->info->win_con)
		sem_post(philo->info->cwin);
	ft_usleep(philo->info->time_to_eat);
	status_message(philo, " is dodoing 💤", 0);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	ft_usleep(philo->info->time_to_sleep);
	status_message(philo, " is pensing 🤔", 0);
	philo->check = 1;
}

void	*loop(t_data *data, int i)
{
	if (i % 2 == 0)
		ft_usleep(data->time_to_eat / 10);
	pthread_create(&data->phil[i].rip, NULL, (void *)rip_timer, &data->phil[i]);
	//pthread_create(&data->phil[i].rips, NULL, (void *)check_rip, &data->phil[i]);
	while (1)
	{
		if (!data->all_deads)
			mangiare(&data->phil[i]);
		else
		{
			break ;
		}
	}
	pthread_join(data->phil[i].rip, NULL);
	pthread_join(data->phil[i].rips, NULL);
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->dead);
	sem_close(data->cwin);
	sem_close(data->ok);
	free(data->phil);
	exit(0);
}
