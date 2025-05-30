/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:05:28 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/30 16:13:03 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *str, int flag)
{
	if (check_death(philo) && flag != DEAD)
		return ;
	pthread_mutex_lock(&philo->data->write_m);
	printf ("%ld %d %s\n", actual_time() - philo->data->start_time,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->write_m);
}

void	loop_check_left(t_philo *philo)
{
	while (!check_death(philo))
	{
		pthread_mutex_lock(&philo->l_f);
		if (philo->status_l == AVAILABLE)
		{
			philo->status_l = UNAVAILABLE;
			pthread_mutex_unlock(&philo->l_f);
			print_status(philo, FORK, ALIVE);
			return ;
		}
		pthread_mutex_unlock(&philo->l_f);
		usleep(50);
	}
}

void	loop_check_right(t_philo *philo)
{
	while (!check_death(philo))
	{
		pthread_mutex_lock(philo->r_f);
		if (*philo->status_r == AVAILABLE)
		{
			*philo->status_r = UNAVAILABLE;
			pthread_mutex_unlock(philo->r_f);
			print_status(philo, FORK, ALIVE);
			return ;
		}
		pthread_mutex_unlock(philo->r_f);
		usleep(50);
	}
}

int	set_fork_available(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_f);
	philo->status_l = AVAILABLE;
	pthread_mutex_unlock(&philo->l_f);
	if (check_death(philo))
		return (DEAD);
	pthread_mutex_lock(philo->r_f);
	*philo->status_r = AVAILABLE;
	pthread_mutex_unlock(philo->r_f);
	return (0);
}
