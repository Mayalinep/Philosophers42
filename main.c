/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:57:51 by maya              #+#    #+#             */
/*   Updated: 2025/03/03 18:48:54 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_thread(char *str, t_rules *rules, int philo_id)
{
	long int	time;

	pthread_mutex_lock(&rules->write_lock);
	time = get_current_time() - rules->simulation_start;
	if (!check_loop(rules))
		printf("%ld %d %s\n", time, philo_id, str);
	pthread_mutex_unlock(&rules->write_lock);
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	t_philo			philos[200];
	pthread_mutex_t	*forks_array;

	if (argc != 5 && argc != 6)
		return (error("mauvais nbr d arguments"));
	if (parsing_args(&rules, argv) != 0)
		return (1);
	rules.philos = philos;
	forks_array = malloc(sizeof(pthread_mutex_t) * rules.nb_philos);
	if (!forks_array)
		return (error("erreur allocation mémoire"));
	rules.forks_array = forks_array;
	init_mutex_rules(&rules);
	init_forks(&rules);
	init_philos(&rules);
	if (thread_create(&rules) != 0)
	{
		free(forks_array);
		return (error("erreur création de threads"));
	}
	cleanup(&rules);
	free(forks_array);
	return (0);
}
