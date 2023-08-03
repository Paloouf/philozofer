/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:35:57 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/03 15:02:11 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data)
{
	int		i;
	long	result;

	i = 0;
	while (i < data->num_of_phil)
	{
		rip_timer(&data->phil[i]);
		if (data->phil[i].is_dead)
		{
			result = get_time() - data->start_time;
			printf("%ld ms %d %s", result,
				data->phil[i].p_num + 1, " is kill 💀\n");
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

int	is_win(t_data *data)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (i < data->num_of_phil)
	{
		if (data->phil[i].eat_count >= data->win_con && data->win_con != 0)
			result++;
		i++;
	}
	if (result == data->num_of_phil && data->win_con != 0)
	{
		i = 0;
		while (i < data->num_of_phil)
		{
			data->phil[i].is_dead = 1;
			i++;
		}
		printf("🤮🤮🤮 Too much spaghetti 🤮🤮🤮\n");
		ft_exit(data);
		return (0);
	}
	return (1);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		pthread_join(data->phil[i].th_id, NULL);
		i++;
	}
	free(data->phil);
	return ;
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
	while (1 > 0)
	{
		if (!is_dead(&data))
			break ;
		if (!is_win(&data))
			break ;
	}
	return (0);
}
