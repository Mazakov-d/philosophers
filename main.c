/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:03:41 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/27 12:08:13 by dorianmazar      ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_all	all;

	if (parsing(ac, av ,&all.data))
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