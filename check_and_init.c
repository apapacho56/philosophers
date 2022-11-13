/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aparedes <aparedes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:17:55 by aparedes          #+#    #+#             */
/*   Updated: 2022/11/13 17:36:34 by aparedes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_data *data, int args, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (args == 6)
		data->musteat = ft_atoi(argv[5]);
	else
		data->musteat = 2147483647;
	if (data->n_philo < 1 || data->t_die < 1
		|| data->t_eat < 1 || data->t_sleep < 1
		|| data->musteat < 1)
		return (1);
	return (0);
}

int	check_and_init(t_data *data, int args, char **argv)
{
	int	i;
	int	read;

	if (args == 5 || args == 6)
	{
		read = 1;
		while (read < args)
		{
			i = 0;
			while (argv[read][i])
			{
				if (argv[read][i] < 48 || argv[read][i] > 57)
				{
					return (ft_error());
				}
				i++;
			}
			read++;
		}
		if (init_args(data, args, argv))
			return (ft_error());
	}
	else
		return (ft_error());
	return (1);
}

int	create_forks(t_data *data, int n_philo)
{
	int	i;

	data->forks = malloc(sizeof(t_mutex) * n_philo);
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (-1);
		i++;
	}
	return (1);
}

int	create_table(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	gettimeofday(&data->t_start, NULL);
	if (!create_forks(data, data->n_philo) || !data->philo)
		return (ft_error());
	if (pthread_create(&data->id_thread, NULL, &thread_monitor, data))
		return (ft_error());
	i = 0;
	data->run = 1;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo,
				&data->philo[i]))
			return (ft_error());
		data->philo[i].data = data;
		data->philo[i].pos = i + 1;
		data->philo[i].eated = 0;
		data->philo[i].fork_l = &data->forks[i];
		data->philo[i].fork_r = &data->forks[(i + data->n_philo - 1)
			% data->n_philo];
		gettimeofday(&data->philo[i].last_meal, NULL);
		i++;
	}
	return (1);
}

int	ft_error(void)
{
	printf("\nError\n");
	printf("Input Order Should be: ./philo {Number of Philosophers} ");
	return (0);
}
