/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:04:25 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/28 15:22:05 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nbr)
{
	long int	nb;
	int			sign;
	int			i;

	i = 0;
	nb = 0;
	sign = 1;
	if (nbr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (-1);
		nb = nb * 10 + (nbr[i] - '0');
		i++;
	}
	if ((nb > 2147483647 && sign == 1) || (nb > 2147483648 && sign == -1))
		return (-1);
	return ((int)nb * sign);
}

int	parsing(int ac, char **av, t_data *data)
{
	if (ac == 5 || ac == 6)
	{
		data->nb_philo = ft_atoi(av[1]);
		data->time_die = ft_atoi(av[2]);
		data->time_eat = ft_atoi(av[3]);
		data->time_sleep = ft_atoi(av[4]);
		data->nb_philo_finish = 0;
		data->status = ALIVE;
		data->nb_eat = -1;
		if (ac == 6)
			data->nb_eat = ft_atoi(av[5]);
		if (data->nb_philo <= 0 || data->time_die <= 0 || data->time_eat <= 0
			|| data->time_sleep <= 0 || (ac == 6 && data->nb_eat <= 0))
			return (1);
		data->start_time = actual_time();
		return (0);
	}
	return (1);
}
