/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_monito.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:43:31 by mpelage           #+#    #+#             */
/*   Updated: 2025/02/28 07:33:28 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(&philo->rules->meal_lock);
	if (get_current_time() - philo->last_meal_time >= time_to_die)
	{
		pthread_mutex_unlock(&philo->rules->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->meal_lock);
	return (0);
}

int	who_is_dead(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		if (philo_dead(&rules->philos[i], rules->time_to_die))
		{
			display_thread("died", rules, rules->philos[i].philo_id);
			pthread_mutex_lock(&rules->death_lock);
			rules->sim_state = 1;
			pthread_mutex_unlock(&rules->death_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_eaten(t_rules *rules)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (rules->min_meals == -1)
		return (0);
	while (i < rules->nb_philos)
	{
		pthread_mutex_lock(&rules->meal_lock);
		if ((int)rules->philos[i].meals_eaten >= rules->min_meals)
			finished++;
		pthread_mutex_unlock(&rules->meal_lock);
		i++;
	}
	if (finished == rules->nb_philos)
	{
		pthread_mutex_lock(&rules->meal_lock);
		pthread_mutex_lock(&rules->death_lock);
		rules->sim_state = 2;
		pthread_mutex_unlock(&rules->meal_lock);
		pthread_mutex_unlock(&rules->death_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (1)
	{
		if (who_is_dead(rules) == 1 || all_eaten(rules) == 1)
			break ;
	}
	return (arg);
}
