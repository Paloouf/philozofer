/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:32:50 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/10 11:03:09 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_message(t_philo *philo, char *str)
{
	long	result;

	pthread_mutex_lock(&philo->info->print);
	pthread_mutex_lock(&philo->info->death);
	if (!*philo->is_dead)
	{
		result = get_time() - philo->info->start_time;
		printf("%ld ms %d %s\n", result, philo->p_num + 1, str);
	}
	pthread_mutex_unlock(&philo->info->death);
	pthread_mutex_unlock(&philo->info->print);
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

int	rip_timer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		data->phil[i].rip_timer = data->time_to_die
			- (get_time() - data->start_time);
		pthread_mutex_lock(&data->mooteks);
		if (get_time() - data->phil[i].time_since_eat > data->time_to_die)
		{
			data->d_statu = 1;
			pthread_mutex_unlock(&data->mooteks);
			return (0);
		}
		pthread_mutex_unlock(&data->mooteks);
		i++;
	}
	return (1);
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
		if (ft_atoi(argv[i]) < 2)
		{
			printf("Arguments must be above 1\n");
			exit(2);
		}
		i++;
	}
}
