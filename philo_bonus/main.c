/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:35:57 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/11 13:54:00 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_data *data)
{
	sem_wait(data->dead);
	sem_wait(data->all_deady);
	data->all_deads = 1;
	sem_post(data->all_deady);
}

void	is_win(t_data *data)
{
	int	i;

	i = 0;
	if (data->win_con != 0)
	{
		while (i < data->num_of_phil)
		{
			sem_wait(data->cwin);
			i++;
		}
		sem_wait(data->cwinny);
		data->win = 1;
		sem_post(data->cwinny);
	}
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->num_of_phil)
	{
		sem_post(data->cwin);
		i++;
	}
	i = 0;
	while (i < data->num_of_phil)
	{
		kill(data->phil[i].pid, SIGKILL);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->cwinny);
	sem_close(data->all_deady);
	sem_close(data->print);
	sem_close(data->timer);
	sem_close(data->dead);
	sem_close(data->cwin);
	sem_close(data->is_deady);
	return ;
}

void	loop_main(t_data *data)
{
	while (1)
	{
		sem_wait(data->cwinny);
		if (data->win)
		{
			status_message(&data->phil[0], " winned", 1);
			ft_exit(data);
			break ;
		}
		sem_post(data->cwinny);
		sem_wait(data->all_deady);
		if (data->all_deads)
		{
			ft_exit(data);
			break ;
		}
		sem_post(data->all_deady);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
		init_params(&data, argc, argv);
	else
	{
		printf("Usage: -number of philosophers -time_to_die");
		printf(" -time_to_eat -time_to_sleep -[number of times to eat]\n");
		return (0);
	}
	init_philos(&data);
	pthread_create(&data.dead_id, NULL, (void *)is_dead, &data);
	pthread_create(&data.win_id, NULL, (void *)is_win, &data);
	pthread_detach(data.dead_id);
	pthread_detach(data.win_id);
	loop_main(&data);
	free(data.phil);
	return (0);
}
