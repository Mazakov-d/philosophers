/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:22:06 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/27 12:14:37 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	if (philo->id % 2)
		usleep(50);
	while (!check_death(philo))
	{
		eat(philo);
		if (check_death(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}

int	routine_launcher(t_all *all)
{
	int i;

	i = 0;
	while(i < all->data.nb_philo)
	{
		pthread_create(&all->philos[i].philo, NULL, routine, &all->philos[i]);
		i++;
	}
	i = 0;
	while (i < all->data.nb_philo)
	{
		pthread_join(all->philos[i].philo, NULL);
		i++;
	}
	return (0);
}