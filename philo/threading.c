/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:59:30 by dmazari           #+#    #+#             */
/*   Updated: 2025/06/09 13:25:28 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	eat_next(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_m);
	if (philo->nb_eat == philo->data->nb_eat)
		philo->data->nb_philo_finish += 1;
	pthread_mutex_unlock(&philo->data->meal_m);
	if (print_status(philo, THINK, ALIVE))
		return (1);
	usleep(50);
	return (0);
}

int	eat(t_philo *philo)
{
	int	fork;

	fork = 0;
	if (!philo->r_f)
	{
		ft_usleep(philo, philo->data->time_die);
		return (1);
	}
	while (fork != 3 && !check_death(philo))
	{
		if (fork != 1)
			fork += take_left_fork(philo);
		if (fork != 2)
			fork += take_right_fork(philo);
	}
	if (print_status(philo, FORK, ALIVE))
		return (1);
	print_status(philo, FORK, DEAD);
	print_status(philo, EAT, DEAD);
	philo->last_eat = actual_time() - philo->data->start_time;
	ft_usleep(philo, philo->data->time_eat);
	set_fork_available(philo);
	philo->nb_eat += 1;
	return (eat_next(philo));
}

int	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP, DEAD);
	if (ft_usleep(philo, philo->data->time_sleep))
		return (1);
	print_status(philo, THINK, DEAD);
	usleep(50);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		status;

	philo = (t_philo *)arg;
	status = WAIT;
	while (status == WAIT)
	{
		pthread_mutex_lock(&philo->data->status_m);
		status = philo->data->status;
		pthread_mutex_unlock(&philo->data->status_m);
		if (status == CRASH)
			return (NULL);
		if (status == READY)
			break ;
	}
	if (philo->id % 2)
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
