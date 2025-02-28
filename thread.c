/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:37:23 by maya              #+#    #+#             */
/*   Updated: 2025/02/28 07:32:53 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_loop(t_rules *rules)
{
	int	state;

	pthread_mutex_lock(&rules->death_lock);
	state = rules->sim_state;
	pthread_mutex_unlock(&rules->death_lock);
	return (state != 0);
}

int	thread_create(t_rules *rules)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < rules->nb_philos)
	{
		if (pthread_create(&rules->philos[i].thread_id, NULL, &routine,
				&rules->philos[i]) != 0)
			exit_fail("erreur creation thread_philo", rules);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, rules->philos) != 0)
		exit_fail("erreur creation thread monitor", rules);
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		exit_fail("erreur join thread monitor", rules);
	while (i < rules->nb_philos)
	{
		if (pthread_join(rules->philos[i].thread_id, NULL) != 0)
			exit_fail("erreur join thread_philo", rules);
		i++;
	}
	return (0);
}
