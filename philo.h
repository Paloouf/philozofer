/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:57:52 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/02 17:39:03 by ltressen         ###   ########.fr       */
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
	int	eat_count;
	long	time_since_eat;
	int	fork_status;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	int	eat_status;
	int	sleep_status;
	int	think_status;
	int	is_dead;
	long	rip_timer;
	struct s_data	*info;
} t_philo;

typedef struct s_data
{
	long	start_time;
	int	num_of_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	win_con;
	pthread_mutex_t	print;
	t_philo	*phil;
} t_data;

int	ft_atoi(const char *str);
void	status_message(t_philo *philo, char *str);
int	rip_timer(t_philo *philo);
long	get_time();
void	ft_exit(t_data *data);

#endif