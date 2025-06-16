/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:03:41 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/06/16 11:37:45 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_put_error(char *error, int i)
{
	write(2, "Error : ", 9);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (i);
}

void	free_all(t_all *all)
{
	init_destroy_all_mutex(all, DESTROY, all->data.nb_philo);
	free(all->philos);
}

int	routine_launcher(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->data.nb_philo)
	{
		if (pthread_create(&all->philos[i].philo, NULL,
				routine, &all->philos[i]))
		{
			pthread_mutex_lock(&all->data.status_m);
			all->data.status = CRASH;
			pthread_mutex_unlock(&all->data.status_m);
			break ;
		}
	}
	pthread_mutex_lock(&all->data.status_m);
	all->data.status = READY;
	all->data.start_time = actual_time();
	pthread_mutex_unlock(&all->data.status_m);
	i--;
	while (i >= 0)
	{
		pthread_join(all->philos[i].philo, NULL);
		i--;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (parsing(ac, av, &all.data))
		return (ft_put_error("Arguments invalids.", 1));
	all.philos = malloc(sizeof(t_philo) * all.data.nb_philo);
	if (!all.philos)
		return (ft_put_error("Philos's malloc.", 1));
	if (set_philos(&all))
		return (ft_put_error("Creating mutex.", 1));
	routine_launcher(&all);
	free_all(&all);
	return (0);
}
