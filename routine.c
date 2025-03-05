/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:04:49 by mpelage           #+#    #+#             */
/*   Updated: 2025/03/05 11:49:11 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_and_think(t_philo *philo)
{
	display_thread("is sleeping", philo->rules, philo->philo_id);
	ft_usleep(philo->rules->time_to_sleep);
	display_thread("is thinking", philo->rules, philo->philo_id);
	if (philo->rules->nb_philos % 2 != 0)
		ft_usleep(philo->rules->time_to_eat);
}

void	get_forks(t_philo *philo, pthread_mutex_t **fork_low,
		pthread_mutex_t **fork_high)
{
	int	left_id;
	int	right_id;

	left_id = (philo->philo_id - 1);
	right_id = philo->philo_id % philo->rules->nb_philos;
	if (left_id < 0)
		left_id = philo->rules->nb_philos - 1;
	if (left_id < right_id)
	{
		*fork_low = philo->left_fork;
		*fork_high = philo->right_fork;
	}
	else
	{
		*fork_low = philo->right_fork;
		*fork_high = philo->left_fork;
	}
}

void	perform_eating(t_philo *philo, pthread_mutex_t *fork_low,
		pthread_mutex_t *fork_high)
{
	if (philo->rules->nb_philos == 1)
	{
		ft_usleep(philo->rules->time_to_die);
		pthread_mutex_unlock(fork_low);
		return ;
	}
	pthread_mutex_lock(fork_high);
	display_thread("has taken a fork", philo->rules, philo->philo_id);
	pthread_mutex_lock(&philo->rules->meal_lock);
	display_thread("is eating", philo->rules, philo->philo_id);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->meal_lock);
	ft_usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(fork_high);
	pthread_mutex_unlock(fork_low);
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*fork_low;
	pthread_mutex_t	*fork_high;

	pthread_mutex_lock(&philo->rules->meal_lock);
	if (philo->is_done)
	{
		pthread_mutex_unlock(&philo->rules->meal_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->meal_lock);
	get_forks(philo, &fork_low, &fork_high);
	pthread_mutex_lock(fork_low);
	display_thread("has taken a fork", philo->rules, philo->philo_id);
	perform_eating(philo, fork_low, fork_high);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(8);
	while (check_loop(philo->rules) == 0)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (arg);
}
