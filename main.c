/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:08:45 by dmazari           #+#    #+#             */
/*   Updated: 2025/03/14 17:49:32 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
	#include <stdio.h>

void    print_data(t_data *data)
{
    printf("Philosophers configuration:\n");
    printf("---------------------------\n");
    printf("Number of philosophers: %d\n", data->nb_philo);
    printf("Time to die:           %d ms\n", data->time_die);
    printf("Time to eat:           %d ms\n", data->time_eat);
    printf("Time to sleep:         %d ms\n", data->time_sleep);
    
    if (data->nb_eat > 0)
        printf("Number of meals:       %d\n", data->nb_eat);
    else
        printf("Number of meals:       unlimited\n");
    printf("---------------------------\n");
}

int	ft_atoi(char *nbr)
{
	long int	nb;
	int			i;
	int			sign;

	if (!nbr)
		return (-1);
	i = 0;
	nb = 0;
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (-1);
		nb = (nb * 10) + (nbr[i] - '0');
		i++;
	}
	return (nb);
}

int	get_data(char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[0]);
	data->time_die = ft_atoi(av[1]);
	data->time_eat = ft_atoi(av[2]);
	data->time_sleep = ft_atoi(av[3]);
	if (av[4])
	{
		data->nb_eat = ft_atoi(av[4]);
		if (data->nb_eat == -1)
			return (1);
	}
	else
		data->nb_eat = -1;
	if (data->nb_philo == -1 || data->time_die == -1
		|| data->time_eat == -1 || data->time_sleep == -1)
		return (1);
	return (0);
}
int	craete_philos(t_data *data, t_philo *philos)
{
	int	i;

	philos = malloc(sizeof(t_philo));
	if (!philos)
		return (1);
	i = 0;
	while (i < philos->data->nb_philo)
	{
		philos->fork = 1;
		philos->id_philo = 
	}
}

int	philo(int ac, char **av)
{
	t_philo	*philos;
	t_data	data;

	if (get_data(av, &data) == 1)
		return (1);
	create_philos(&data, philos);
	print_data(&data);
	return (0);
}

int	main(int ac, char **av)
{
	int	rtn;

	if (ac != 5 && ac != 6)
	{
		write(2, "Error : arguments\n", 19);
		return (1);
	}
	rtn = philo(ac - 1, av + 1);
	if (rtn == 1)
		write(2, "Error\n", 7);
	return (rtn);
}