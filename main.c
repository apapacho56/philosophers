/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:58:08 by aparedes          #+#    #+#             */
/*   Updated: 2022/11/14 11:04:40 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_monitor(void *phi_data)
{
	int		i;
	int		eated;
	t_data	*data;

	data = (t_data *)phi_data;
	ft_msleep(data->t_die * 0.9);
	while (1)
	{
		i = 0;
		eated = 0;
		while (i < data->n_philo)
		{
			if (data->philo[i].eated >= data->musteat)
				eated++;
			if (is_dead(data, &data->philo[i])
				|| eated == data->n_philo)
			{
				data->run = 0;
				free_threads(data);
				return ((void *)0);
			}
			i++;
		}
		usleep(200);
	}
}

void	output(t_data *data, t_philo *philo, int sig)
{
	int	time;

	time = diff_time(&data->t_started);
	if (sig == 1)
		printf("%d %d has taken a fork\n", time, philo->pos);
	else if (sig == 2)
	{
		printf("%d %d is eating\n", time, philo->pos);
		gettimeofday(&philo->last_meal, NULL);
		philo->eated++;
		ft_msleep(philo->data->t_eat);
	}
	else if (sig == 3)
	{
		printf("%d %d is sleeping\n", time, philo->pos);
		ft_msleep(data->t_sleep);
	}
	else if (sig == 4)
		printf("%d %d is thinking\n", time, philo->pos);
	else if (sig == 5)
		printf("%d %d died\n", time, philo->pos);
}

void	*philo(void *pt_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pt_philo;
	if (philo->pos % 2 == 0)
		ft_msleep(philo->data->t_eat * 0.9);
	while (philo->data->run == 1)
	{
		pthread_mutex_lock(philo->fork_l);
		output(philo->data, philo, 1);
		pthread_mutex_lock(philo->fork_r);
		output(philo->data, philo, 1);
		output(philo->data, philo, 2);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		output(philo->data, philo, 3);
		output(philo->data, philo, 4);
	}
	return ((void *)-1);
}

int	main(int args, char **argv)
{
	t_data	data;
	int		i;

	if (check_and_init(&data, args, argv) && create_table(&data))
	{
		i = 0;
		pthread_join(data.th_monitor, NULL);
		while (i < data.n_philo && data.run == 1)
		{
			pthread_join(data.philo[i].thread, NULL);
			i++;
		}
		free_threads(&data);
	}
	return (0);
}
