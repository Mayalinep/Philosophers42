/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:04:49 by mpelage           #+#    #+#             */
/*   Updated: 2025/02/28 07:32:48 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_and_think(t_philo *philo)
{
	display_thread("is sleeping", philo->rules, philo->philo_id);
	ft_usleep(philo->rules->time_to_sleep);
	display_thread("is thinking", philo->rules, philo->philo_id);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	display_thread("has taken a fork", philo->rules, philo->philo_id);
	if (philo->rules->nb_philos == 1)
	{
		ft_usleep(philo->rules->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	display_thread("has taken a fork", philo->rules, philo->philo_id);
	display_thread("is eating", philo->rules, philo->philo_id);
	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (check_loop(philo->rules) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (arg);
}
