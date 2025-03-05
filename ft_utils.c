/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:28:13 by maya              #+#    #+#             */
/*   Updated: 2025/03/03 12:40:08 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	printf("Erreur %s\n", str);
	return (1);
}

int	exit_fail(char *str, t_rules *rules)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	pthread_mutex_destroy(&rules->write_lock);
	pthread_mutex_destroy(&rules->death_lock);
	pthread_mutex_destroy(&rules->meal_lock);
	while (i < rules->nb_philos)
	{
		pthread_mutex_destroy(&rules->forks_array[i]);
		i++;
	}
	return (1);
}

void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&rules->write_lock);
	pthread_mutex_destroy(&rules->death_lock);
	pthread_mutex_destroy(&rules->meal_lock);
	while (i < rules->nb_philos)
	{
		pthread_mutex_destroy(&rules->forks_array[i]);
		i++;
	}
}

long int	get_current_time(void)
{
	struct timeval	tv;
	long int		time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_mill);
}

void	ft_usleep(long int time)
{
	long int	start;

	start = get_current_time();
	while (get_current_time() - start < time)
		usleep(500);
}
