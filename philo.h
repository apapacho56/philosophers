/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:09:07 by aparedes          #+#    #+#             */
/*   Updated: 2022/11/14 11:51:00 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				pos;
	int				eated;
	pthread_t		thread;
	t_mutex			*fork_r;
	t_mutex			*fork_l;
	struct s_data	*data;
	struct timeval	last_meal;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	t_mutex			*forks;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				musteat;
	int				run;
	pthread_t		th_monitor;
	struct timeval	t_started;
}	t_data;

int		create_table(t_data *data);
int		check_and_init(t_data *data, int args, char **argv);
void	ft_msleep(long ms);
int		diff_time(struct timeval *begin);
void	*thread_monitor(void *phi_data);
int		is_dead(t_data *data, t_philo *philo);
void	output(t_data *data, t_philo *philo, int sig);
void	*philo(void *pt_philo);
int		free_threads(t_data *data);
int		ft_atoi(const char *str);
int		ft_error(void);

#endif