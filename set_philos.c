/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:43:07 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/27 13:08:34 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_destroy_mutex_data(t_data *data, int flag)
{
	if (flag == INIT && pthread_mutex_init(&data->write_m, NULL) != 0)
		return (1);
	if (flag == INIT && pthread_mutex_init(&data->eat_m, NULL) != 0)
		return (pthread_mutex_destroy(&data->write_m), 1);
	if (flag == INIT && pthread_mutex_init(&data->status_m, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_m);
		pthread_mutex_destroy(&data->eat_m);
		return (1);
	}
	if ((flag == INIT && pthread_mutex_init(&data->meal_m, NULL) != 0) || flag == DESTROY)
	{
		pthread_mutex_destroy(&data->write_m);
		pthread_mutex_destroy(&data->eat_m);
		pthread_mutex_destroy(&data->status_m);
		if (flag == INIT)
			return (1);
		else
		{
			pthread_mutex_destroy(&data->meal_m);
			return (0);
		}
		}
	return (0);
}

int	init_destroy_all_mutex(t_all *all, int flag, int max)
{
	int	i;

	i = 0;
	if (init_destroy_mutex_data(&all->data, flag))
		return (1);
	while (i < max)
	{
		if (flag == INIT)
		{
			if (pthread_mutex_init(&all->philos[i].l_f, NULL) != 0)
			{
				init_destroy_all_mutex(all, DESTROY, i);
				return (1);
			}
		}
		else
			pthread_mutex_destroy(&all->philos[i].l_f);
		i++;
	}
	return (0);
}

int	set_philos(t_all *all)
{
	int	i;

	i = 0;
	if (init_destroy_all_mutex(all, INIT, all->data.nb_philo) != 0)
	{
		free(all->philos);
		return (1);
	}
	while (i < all->data.nb_philo)
	{
		all->philos[i].id = i + 1;
		all->philos[i].nb_philos = all->data.nb_philo;
		all->philos[i].nb_eat = 0;
		all->philos[i].data = &all->data;
		if (i < all->data.nb_philo - 1)
			all->philos[i].r_f = &all->philos[i + 1].l_f;
		else
			all->philos[i].r_f = &all->philos[0].l_f;
		i++;
	}
	return (0);
}
