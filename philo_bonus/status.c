/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:32:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/15 16:41:52 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_message(t_philo *philo, char *str, int flag)
{
	long	result;
	int		i;

	i = 0;
	sem_wait(philo->info->print);
	sem_wait(philo->info->is_deady);
	if (!philo->is_dead)
	{
		sem_post(philo->info->is_deady);
		result = get_time() - philo->info->start_time;
		printf("%ld ms %d %s\n", result, philo->p_num + 1, str);
		if (flag == 1)
		{
			while (i <= philo->info->num_of_phil)
			{
				sem_post(philo->info->dead);
				i++;
			}
		}
	}
	else
		sem_post(philo->info->is_deady);
	sem_post(philo->info->print);
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

void	check_arg(char **argv)
{
	int	i;

	i = 2;
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Number of philos must be above 0\n");
		exit(2);
	}
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("Arguments must be above 0\n");
			exit(2);
		}
		i++;
	}
}
