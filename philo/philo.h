/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:57:52 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/09 17:19:31 by ltressen         ###   ########.fr       */
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
	pthread_t		th_id;
	int				p_num;
	int				eat_count;
	pthread_mutex_t	meat_count;
	long			time_since_eat;
	int				fork_status;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;
	int				eat_status;
	int				sleep_status;
	int				think_status;
	int				*is_dead;
	long			rip_timer;
	struct s_data	*info;
}	t_philo;

typedef struct s_data
{
	long			start_time;
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				win_con;
	int				d_statu;
	pthread_mutex_t	mooteks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_philo			*phil;
}	t_data;

int		ft_atoi(const char *str);
void	status_message(t_philo *philo, char *str);
int		rip_timer(t_data *data);
long	get_time(void);
void	ft_exit(t_data *data);
void	ft_usleep(int ms);
void	check_arg(char **argv);
void	init_philos(t_data *data);
void	init_params(t_data *data, int argc, char **argv);
void	*loop(t_philo *phil);
void	mangiare(t_philo *philo);

#endif
