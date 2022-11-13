/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:18:22 by aparedes          #+#    #+#             */
/*   Updated: 2022/11/13 17:36:48 by aparedes         ###   ########.fr       */
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
	pthread_t		id_thread;
	struct timeval	t_start;
}	t_data;

int		create_table(t_data *dta);
int		check_and_init(t_data *dta, int ac, char **av);

void	ft_msleep(long ms);
int		diff_time(struct timeval *begin);

void	*thread_monitor(void *p_dta);
int		is_dead(t_data *dta, t_philo *philo);
void	output(t_data *dta, t_philo *philo, int sig);
void	*philo(void *t_d_philo);

int		free_threads(t_data *dta);
int		ft_atoi(const char *str);
int		ft_error(void);

#endif