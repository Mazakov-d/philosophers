/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:22:06 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/30 16:00:05 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_next(t_philo *philo)
{
	print_status(philo, EAT, ALIVE);
	philo->last_eat = actual_time() - philo->data->start_time;
	if (ft_usleep(philo, philo->data->time_eat * 1000))
		return ;
	if (set_fork_available(philo))
		return ;
	philo->nb_eat += 1;
	pthread_mutex_lock(&philo->data->meal_m);
	if (philo->nb_eat == philo->data->nb_eat)
	philo->data->nb_philo_finish += 1;
	pthread_mutex_unlock(&philo->data->meal_m);
	if (check_death(philo))
		return ;
	print_status(philo, THINK, ALIVE);
	usleep(10);
}

void	eat(t_philo *philo)
{
	loop_check_left(philo);
	if (check_death(philo))
		return ;
	if (!philo->r_f)
	{
		ft_usleep(philo, philo->data->time_die * 1000);
		return ;
	}
	loop_check_right(philo);
	if (check_death(philo))
			return ;
	eat_next(philo);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP, ALIVE);
	if (ft_usleep(philo, philo->data->time_sleep * 1000))
		return ;
	print_status(philo, THINK, ALIVE);
	usleep(10);
}

int	check_death(t_philo *philo)
{
	long	time;

	time = actual_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->status_m);
	if (philo->data->status == DEAD)
	{
		pthread_mutex_unlock(&philo->data->status_m);
		return (DEAD);
	}
	if ((time - philo->last_eat) >= philo->data->time_die)
	{
		philo->data->status = DEAD;
		pthread_mutex_unlock(&philo->data->status_m);
		print_status(philo, DIED, DEAD);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->data->status_m);
	pthread_mutex_lock(&philo->data->meal_m);
	if (philo->data->nb_philo_finish >= philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->meal_m);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->data->meal_m);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(100);
	while (!check_death(philo))
	{
		eat(philo);
		if (check_death(philo))
			break ;
		sleeping(philo);
	}
	return (NULL);
}
