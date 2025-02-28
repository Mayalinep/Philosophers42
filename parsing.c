/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:02:12 by maya              #+#    #+#             */
/*   Updated: 2025/02/28 07:33:15 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valide_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (error("Arguments invalides"));
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	parsing_args(t_rules *rules, char **argv)
{
	if (valide_args(argv) != 0)
		return (1);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (error("Nombre de philosophes invalide"));
	if (ft_atoi(argv[2]) <= 0)
		return (error("Temps avant la mort invalide"));
	if (ft_atoi(argv[3]) <= 0)
		return (error("Temps pour manger invalide"));
	if (ft_atoi(argv[4]) <= 0)
		return (error("Temps pour dormir invalide"));
	if (argv[5] && ft_atoi(argv[5]) < 1)
		return (error("Nombre de repas invalide"));
	init_rules(rules, argv);
	return (0);
}
