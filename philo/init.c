/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:58:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/10 11:00:50 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_params(t_data *data, int argc, char **argv)
{
	check_arg(argv);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->mooteks, NULL);
	data->d_statu = 0;
	data->start_time = get_time();
	data->num_of_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->win_con = ft_atoi(argv[5]);
	else
		data->win_con = 0;
	data->phil = malloc(sizeof(t_philo) * data->num_of_phil);
}

void	cas_particulier(t_data *data)
{
	long	result;

	result = get_time() - data->start_time;
	printf("%ld ms 1 has taken a fork 🍴\n", result);
}

void	philo_suite(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_phil == 1)
	{
		cas_particulier(data);
		return ;
	}
	while (i < data->num_of_phil)
	{
		if (i == data->num_of_phil - 1)
			data->phil[i].fork_r = &data->phil[0].fork_l;
		else
			data->phil[i].fork_r = &data->phil[i + 1].fork_l;
		pthread_create(&data->phil[i].th_id,
			NULL, (void *)loop, &data->phil[i]);
		i++;
	}
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
		data->phil[i].is_dead = &data->d_statu;
		pthread_mutex_init(&data->phil[i].fork_l, NULL);
		pthread_mutex_init(&data->phil[i].meat_count, NULL);
		i++;
	}
	philo_suite(data);
}
