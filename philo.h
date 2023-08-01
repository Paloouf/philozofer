/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:57:52 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/31 16:28:09 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t	th_ID;
	int	p_num;
	int	fork_status;
	int	eat_status;
	int	sleep_status;
	int	think_status;
	int	is_dead;
} t_philo;

typedef struct s_fork
{
	pthread_mutex_t f_ID;
	int	f_num;
} t_fork;
typedef struct s_data
{
	long	start_time;
	int	num_of_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	win_con;
	int	i;
	t_philo	*phil;
	t_fork	*fork;
} t_data;

int	ft_atoi(const char *str);
void	status_message(t_data *data, int i);

#endif