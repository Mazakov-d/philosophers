/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:30:33 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/28 16:02:45 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INIT 0
# define DESTROY 1

# define ALIVE 0
# define FINISH 1
# define DEAD 2

# define UNAVAILABLE 0
# define AVAILABLE 1

# define LEFT 1

# define EAT "is eating"
# define DIED "died"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	pthread_mutex_t	write_m;
	pthread_mutex_t	eat_m;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	status_m;
	long int		start_time;
	int				nb_philo_finish;
	int				status;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_philos;
	pthread_t		philo;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
	int				*status_r;
	int				status_l;
	t_data			*data;
	long int		last_eat;
	int				nb_eat;
}	t_philo;

typedef struct s_all
{
	t_philo	*philos;
	t_data	data;
}	t_all;

/*
** parsing.c
*/
int			ft_atoi(char *nbr);
int			parsing(int ac, char **av, t_data *data);

/*
** set_philos.c
*/
int			init_destroy_mutex_data(t_data *data, int flag);
int			init_destroy_all_mutex(t_all *all, int flag, int max);
void		set_philos_loop(t_all *all, int i);
int			set_philos(t_all *all);

/*
** utils.c
*/
long int	actual_time(void);
void		print_status(t_philo *philo, char *str);
int			loop_check_left(t_philo *philo);
int			loop_check_right(t_philo *philo);
int			set_fork_available(t_philo *philo);

/*
** threading.c
*/
void		eat_next(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
int			check_death(t_philo *philo);
void		*routine(void *arg);

#endif