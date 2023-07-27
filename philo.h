/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:57:52 by ltressen          #+#    #+#             */
/*   Updated: 2023/07/27 13:44:28 by ltressen         ###   ########.fr       */
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

typedef struct s_data
{
	pthread_t	*th_philo;
	int	num_of_phil;
	pthread_t	*phil_ID;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	win_con;
} t_data;

int	ft_atoi(const char *str);

#endif