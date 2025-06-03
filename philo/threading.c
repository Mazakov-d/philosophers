/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:22:06 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/06/03 11:16:44 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_next(t_philo *philo)
{
	philo->last_eat = actual_time() - philo->data->start_time;
	usleep(philo->data->time_eat * 1000);
	if (set_fork_available(philo))
		return (1);
	philo->nb_eat += 1;
	pthread_mutex_lock(&philo->data->meal_m);
	if (philo->nb_eat == philo->data->nb_eat)
		philo->data->nb_philo_finish += 1;
	pthread_mutex_unlock(&philo->data->meal_m);
	if (print_status(philo, THINK, ALIVE))
		return (1);
	usleep(10);
	return (0);
}

int	eat(t_philo *philo)
{
	if (loop_check_left(philo))
		return (1);
	if (print_status(philo, FORK, ALIVE))
		return (1);
	if (!philo->r_f)
	{
		usleep(philo->data->time_die * 1000);
		return (1);
	}
	if (loop_check_right(philo))
		return (1);
	if (print_status(philo, FORK, ALIVE))
		return (1);
	if (print_status(philo, EAT, ALIVE))
		return (1);
	return (eat_next(philo));
}

int	sleeping(t_philo *philo)
{
	if (print_status(philo, SLEEP, ALIVE))
		return (1);
	usleep(philo->data->time_sleep * 1000);
	if (print_status(philo, THINK, ALIVE))
		return (1);
	usleep(10);
	return (0);
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
	int		flag;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		usleep(50);
	flag = 0;
	while (!flag)
	{
		flag = eat(philo);
		if (flag)
			break ;
		flag = sleeping(philo);
	}
	return (NULL);
}
