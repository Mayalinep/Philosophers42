/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:30:05 by maya              #+#    #+#             */
/*   Updated: 2025/02/28 07:34:22 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(t_rules *rules, char **argv)
{
	rules->nb_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->min_meals = ft_atoi(argv[5]);
	else
		rules->min_meals = -1;
	rules->simulation_start = get_current_time();
	rules->sim_state = 0;
	rules->finished_count = 0;
	rules->philos = NULL;
	rules->forks_array = NULL;
}

void	init_mutex_rules(t_rules *rules)
{
	pthread_mutex_init(&rules->write_lock, NULL);
	pthread_mutex_init(&rules->death_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
}

void	init_forks(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		pthread_mutex_init(&rules->forks_array[i], NULL);
		i++;
	}
}

void	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philos)
	{
		rules->philos[i].philo_id = i;
		rules->philos[i].last_meal_time = rules->simulation_start;
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].is_done = 0;
		rules->philos[i].left_fork = &rules->forks_array[i];
		if (i == rules->nb_philos - 1)
			rules->philos[i].right_fork = &rules->forks_array[0];
		else
			rules->philos[i].right_fork = &rules->forks_array[i + 1];
		rules->philos[i].rules = rules;
		i++;
	}
}
