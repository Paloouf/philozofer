/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:35:57 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/02 18:41:02 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time()
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

void	mangiare(t_philo *philo)
{
	philo->eat_status = 1;
	if (!philo->is_dead)
	{
		philo->fork_status = 1;
		pthread_mutex_lock(&philo->fork_l);
	}
	status_message(philo, " has taken a fork\n");
	if (!philo->is_dead)
	{
		philo->fork_status = 2;
		pthread_mutex_lock(philo->fork_r);
	}
	status_message(philo, " has taken a fork\n");
	status_message(philo, " is manging\n");
	philo->eat_count++;
	ft_usleep(philo->info->time_to_eat);
	philo->time_since_eat = get_time();
	if (philo->fork_status > 0)
		pthread_mutex_unlock(&philo->fork_l);
	if (philo->fork_status > 1)
		pthread_mutex_unlock(philo->fork_r);
	philo->fork_status = 0;
	status_message(philo, " is dodoing\n");
	ft_usleep(philo->info->time_to_sleep);
	status_message(philo, " is pensing\n");
}

int	rip_timer(t_philo *philo)
{
	philo->rip_timer = philo->info->time_to_die - (get_time() - philo->info->start_time);
	if (get_time() - philo->time_since_eat > philo->info->time_to_die)
	{
		philo->info->phil[philo->p_num].is_dead = 1;
		status_message(philo, "is kill\n");
		return (0);
		//ft_exit(philo->info);
	}
	return (1);
}
//fonction que le philo doit suivre pour manger, dormir, penser et (ne pas) mourir.
void	*loop(t_philo *phil)
{
	t_philo	*philo;

	philo = (t_philo *)phil;
	if (philo->p_num % 2 == 0)
		ft_usleep(philo->info->time_to_eat / 10);
	while (1)
	{
		if (!philo->is_dead)
			mangiare(philo);
		else
			break ;
	}
	philo->is_dead = 1;
	return (NULL);
}

void	init_params(t_data *data, int argc, char **argv)
{
	pthread_mutex_init(&data->print, NULL);
	data->start_time = get_time();
	data->num_of_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->win_con = ft_atoi(argv[5]);
	data->phil = malloc(sizeof(t_philo) * data->num_of_phil);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		data->phil[i].p_num = i;
		data->phil[i].eat_status = 0;
		data->phil[i].fork_r = NULL;
		data->phil[i].info = data;
		data->phil[i].eat_count = 0;
		data->phil[i].time_since_eat = get_time();
		data->phil[i].fork_status = 0;
		data->phil[i].sleep_status = 0;
		data->phil[i].think_status = 0;
		data->phil[i].is_dead = 0;
		pthread_mutex_init(&data->phil[i].fork_l, NULL);
		i++;
	}
	i = 0 ;
	while (i < data->num_of_phil)
	{
		if (i == data->num_of_phil - 1)
			data->phil[i].fork_r = &data->phil[0].fork_l;
		else
			data->phil[i].fork_r = &data->phil[i + 1].fork_l;
		pthread_create(&data->phil[i].th_ID, NULL, (void *)loop, &data->phil[i]);
		i++;
	}
}

int	is_dead(t_data *data)
{
	int	i;
	long	result;

	i = 0;
	while (i < data->num_of_phil)
	{
		rip_timer(&data->phil[i]);
		if (data->phil[i].is_dead)
		{
			result = get_time() - data->start_time;
			printf("%ld ms %d %s", result, data->phil[i].p_num + 1, " is kill\n");
			i = 0;
			while (i < data->num_of_phil)
			{
				data->phil[i].is_dead = 1;
				i++;
			}
			ft_exit(data);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		pthread_join(data->phil[i].th_ID, NULL);
		i++;
	}
	free(data->phil);
	return ;
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
		init_params(&data, argc, argv);
	else
		return (printf("Usage: -number of philosophers -time_to_die -time_to_eat -time_to_sleep -[number of times to eat]\n"), 0);	
	init_philos(&data);
	while (1 > 0)
		if (!is_dead(&data))
			break ;
	return (0);
}