/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:52:08 by aparedes          #+#    #+#             */
/*   Updated: 2022/11/14 11:56:00 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msleep(long ms)
{
	struct timeval	begin;
	long			res;

	gettimeofday(&begin, NULL);
	res = 0;
	while (res < ms)
	{
		usleep(100);
		res = diff_time(&begin);
	}
}

int	free_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}

int	diff_time(struct timeval *begin)
{
	struct timeval	now;
	int				time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec - begin->tv_sec) * 1000 + \
		(now.tv_usec - begin->tv_usec) / 1000;
	return (time);
}

int	is_dead(t_data *data, t_philo *philo)
{
	long	time;

	time = diff_time(&philo->last_meal);
	if (time >= data->t_die)
	{
		output(data, philo, 5);
		philo->eated = data->musteat + 1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	len;
	int	num;

	num = 0;
	len = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num + str[i] - '0';
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			num *= 10;
		if (len > 10 || num > 2147483647)
			return (-1);
		len++;
		i++;
	}
	return (num);
}
