/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 08:57:52 by ltressen          #+#    #+#             */
/*   Updated: 2023/08/10 16:40:28 by ltressen         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_philo
{
	pthread_t		th_id;
	pthread_t		rip;
	pthread_t		rips;
	int				p_num;
	int				eat_count;
	long			time_since_eat;
	int				fork_status;
	int				eat_status;
	int				sleep_status;
	int				think_status;
	int				is_dead;
	int				pid;
	int				check;
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
	int				all_deads;
	int				win;
	pthread_t			dead_id;
	pthread_t			win_id;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*dead;
	sem_t	*cwin;
	sem_t	*ok;
	sem_t	*is_deady;
	t_philo			*phil;
}	t_data;

int		ft_atoi(const char *str);
void	status_message(t_philo *philo, char *str, int flag);
void		rip_timer(t_philo *philo);
long	get_time(void);
void	ft_exit(t_data *data);
void	ft_usleep(int ms);
void	check_arg(char **argv);
void	init_philos(t_data *data);
void	init_params(t_data *data, int argc, char **argv);
void	*loop(t_data *data, int i);
void	mangiare(t_philo *philo);

#endif