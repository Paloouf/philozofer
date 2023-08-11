/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:58:08 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/11 13:47:04 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sem(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/cwin");
	sem_unlink("/ok");
	sem_unlink("/is_deady");
	sem_unlink("/timer");
	sem_unlink("/all_deady");
	sem_unlink("/cwinny");
	data->forks = sem_open("/forks", O_CREAT, 0777, (int)data->num_of_phil - 1);
	sem_post(data->forks);
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	data->all_deady = sem_open("/all_deady", O_CREAT, 0644, 1);
	data->cwinny = sem_open("/cwinny", O_CREAT, 0644, 1);
	data->dead = sem_open("/dead", O_CREAT, 0644, 0);
	data->cwin = sem_open("/cwin", O_CREAT, 0644, 0);
	data->is_deady = sem_open("/is_deady", O_CREAT, 0644, 1);
	data->timer = sem_open("/timer", O_CREAT, 0644, 1);
}

void	init_params(t_data *data, int argc, char **argv)
{
	check_arg(argv);
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
	data->dead = 0;
	data->all_deads = 0;
	data->win = 0;
	init_sem(data);
}

void	philo_suite(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		data->phil[i].pid = fork ();
		if (data->phil[i].pid == 0)
			loop(data, i);
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		data->phil[i].check = 0;
		data->phil[i].p_num = i;
		data->phil[i].eat_status = 0;
		data->phil[i].info = data;
		data->phil[i].eat_count = 0;
		data->phil[i].time_since_eat = get_time();
		data->phil[i].fork_status = 0;
		data->phil[i].sleep_status = 0;
		data->phil[i].think_status = 0;
		data->phil[i].is_dead = 0;
		i++;
	}
	philo_suite(data);
}
