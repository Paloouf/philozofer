/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:35:57 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/31 16:42:40 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_data *data)
{
	int	tid;

	tid = data->phil->p_num;
	if (tid == 0)
	{
		pthread_mutex_unlock(&data->fork[tid].f_ID);
		pthread_mutex_unlock(&data->fork[data->num_of_phil - 1].f_ID);
	}
	else
	{
		pthread_mutex_unlock(&data->fork[tid].f_ID);
		pthread_mutex_unlock(&data->fork[tid - 1].f_ID);
	}
	data->phil->eat_status = 1;
	data->phil->fork_status = 0;
	status_message(data, data->i);
	data->phil->eat_status = 0;

}

void	forquetta(t_data *data)
{
	int	tid;

	tid = data->phil->p_num;
	//printf("%d\n", tid);
	if (tid == 0)
	{
		pthread_mutex_lock(&data->fork[tid].f_ID);
		pthread_mutex_lock(&data->fork[data->num_of_phil - 1].f_ID);
	}
	else
	{
		pthread_mutex_lock(&data->fork[tid].f_ID);
		pthread_mutex_lock(&data->fork[tid - 1].f_ID);
	}
	data->phil->fork_status = 1;
	status_message(data, data->i);
}

//fonction que le philo doit suivre pour manger, dormir, penser et (ne pas) mourir.
void	*loop(t_data *data)
{
	pthread_t tid;

	printf("th_id : %ld\n", data->phil[data->i].th_ID);
	tid = pthread_self();
	printf("tid : %ld\n", tid);
	printf("%d\n", data->phil[data->i].p_num);
	if (1)//data->phil->fork_status == 0 && data->num_of_phil > 1)
	{
		forquetta(data);
	}
	if (data->phil->fork_status == 1 && data->phil->eat_status == 0 && data->time_to_eat > 0)
	{
		eating(data);
	}
	return (NULL);
}

void	init_params(t_data *data, int argc, char **argv)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->num_of_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->win_con = ft_atoi(argv[5]);
	data->phil = malloc(sizeof(t_philo) * data->num_of_phil);
	data->fork = malloc(sizeof(t_fork) * data->num_of_phil);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->i = 0;
	while (i < data->num_of_phil)
	{
		data->phil[i].p_num = i;
		data->phil[i].eat_status = 0;
		data->phil[i].fork_status = 0;
		data->phil[i].sleep_status = 0;
		data->phil[i].think_status = 0;
		data->phil[i].is_dead = 0;
		pthread_create(&data->phil[data->i].th_ID, NULL, (void *)loop, data);
		pthread_join(data->phil[data->i].th_ID, NULL);
		data->i++;
		usleep(300);
		i++;
	}
	i = 0 ;
	while (i < data->num_of_phil)
		printf("tid : %ld\n", data->phil[i++].th_ID);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_phil)
	{
		data->fork[i].f_num = i;
		pthread_mutex_init(&data->fork[i].f_ID, NULL);
		usleep(300);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data	data;
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
		init_params(&data, argc, argv);
	else
		return (printf("Usage: -number of philosophers -time_to_die -time_to_eat -time_to_sleep -[number of times to eat]\n"), 0);	
	init_forks(&data);
	init_philos(&data);
	while (i < data.num_of_phil)
	{
		pthread_detach(data.phil[i].th_ID);
		i++;
	}
	free(data.phil);
	free(data.fork);
	return (0);
}