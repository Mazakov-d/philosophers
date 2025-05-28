/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorianmazari <dorianmazari@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:05:28 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/27 13:15:41 by dorianmazar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	actual_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *str)
{
	while (pthread_mutex_lock(&philo->data->write_m))
		usleep(10);
	printf("%ld", actual_time() - philo->data->start_time);
	printf(" %d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->data->write_m);
}

void	eat(t_philo *philo)
{
	while(pthread_mutex_lock(&philo->l_f))
		usleep(10);
	print_status(philo, FORK);
	while(pthread_mutex_lock(philo->r_f))
		usleep(10);
	print_status(philo, FORK);
	print_status(philo, EAT);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->l_f);
	pthread_mutex_unlock(philo->r_f);
	philo->nb_eat += 1;
	while (pthread_mutex_lock(&philo->data->meal_m))
		usleep(10);
	if (philo->nb_eat == philo->data->nb_eat)
		philo->data->nb_philo_finish += 1;
	pthread_mutex_unlock(&philo->data->meal_m);
	philo->last_eat = actual_time() - philo->data->start_time;
	print_status(philo, THINK);
	usleep(10);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->data->time_sleep * 1000);
	print_status(philo, THINK);
	usleep(10);
}

int	check_death(t_philo *philo)
{
	long	time;

	time = actual_time() - philo->data->start_time;
	while (pthread_mutex_lock(&philo->data->status_m))
		usleep(10);
	if (philo->data->status == DEAD)
	{
		pthread_mutex_unlock(&philo->data->status_m);
		return (DEAD);
	}
	if (philo->last_eat > 0 && (time - philo->last_eat) >= philo->data->time_die)
	{
		pthread_mutex_unlock(&philo->data->status_m);
		philo->data->status = DEAD;
		print_status(philo, DIED);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->data->status_m);
	while (pthread_mutex_lock(&philo->data->meal_m))
		usleep(10);
	if (philo->data->nb_philo_finish >= philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->meal_m);
		return (FINISH);
	}
	pthread_mutex_unlock(&philo->data->meal_m);
	return (0);
}
