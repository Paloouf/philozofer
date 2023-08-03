/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:32:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/03 16:53:30 by ltressen         ###   ########.fr       */
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
		printf("%ld ms %d %s\n", result, philo->p_num + 1, str);
		pthread_mutex_unlock(&philo->info->print);
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms / 10);
}

int	rip_timer(t_philo *philo)
{
	philo->rip_timer = philo->info->time_to_die
		- (get_time() - philo->info->start_time);
	if (get_time() - philo->time_since_eat > philo->info->time_to_die)
	{
		philo->info->phil[philo->p_num].is_dead = 1;
		status_message(philo, "is kill 💀");
		return (0);
	}
	return (1);
}

void	check_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 2)
		{
			printf("Arguments must be above 1\n");
			exit(2);
		}
		i++;
	}
}
