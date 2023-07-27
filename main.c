/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:35:57 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/27 13:49:04 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*loop(t_data *data)
{
	(void)data;
	static int	i = 0;
	pthread_t	tid;

	tid = pthread_self();
	data->phil_ID[i] = tid;
	printf("Phil_num :%d, Phil_ID: %ld\n", i + 1, tid);
	return (NULL);
}

void	init_all(t_data *data, int argc, char **argv)
{
	int	j;

	data->num_of_phil = ft_atoi(argv[1]);
	data->phil_ID = malloc(sizeof(pthread_t) * data->num_of_phil);
	j = 0;
	while (j < data->num_of_phil)
	{
		data->phil_ID[j] = (pthread_t)j + 1;
		j++;
	}
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->win_con = ft_atoi(argv[5]);
	
}

int main(int argc, char **argv)
{
	t_data	data;
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
		init_all(&data, argc, argv);
	else
		return (printf("Usage: -number of philosophers -time_to_die -time_to_eat -time_to_sleep -[number of times to eat]\n"), 0);	
	while (i < data.num_of_phil)
	{	
		data.th_philo = malloc(sizeof(long unsigned int *) * data.num_of_phil);
		pthread_create(data.phil_ID, NULL, (void *)loop, &data);
		pthread_join(data.phil_ID[i], NULL);
		i++;
	}
	free(data.th_philo);
	free(data.phil_ID);
	return (0);
}