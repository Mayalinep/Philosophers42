/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpelage <mpelage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:57:30 by maya              #+#    #+#             */
/*   Updated: 2025/03/03 18:48:24 by mpelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_meals;

	long int		simulation_start;
	int				sim_state;

	int				finished_count;

	pthread_mutex_t	*forks_array;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;

	struct s_philo	*philos;
}					t_rules;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;

	long int		last_meal_time;
	unsigned int	meals_eaten;
	int				is_done;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_rules			*rules;
}					t_philo;

int					error(char *str);
int					exit_fail(char *str, t_rules *rules);
void				cleanup(t_rules *rules);
long int			get_current_time(void);
void				ft_usleep(long int time);

void				init_forks(t_rules *rules);
void				init_philos(t_rules *rules);
void				init_rules(t_rules *rules, char **argv);
void				init_mutex_rules(t_rules *rules);

int					valide_args(char **argv);
int					ft_atoi(const char *str);
int					parsing_args(t_rules *rules, char **argv);

int					thread_create(t_rules *rules);
void				*routine(void *arg);
void				display_thread(char *str, t_rules *rules, int philo_id);
void				sleep_and_think(t_philo *philo);
void				eat(t_philo *philo);
void				get_forks(t_philo *philo, pthread_mutex_t **fork_low,
						pthread_mutex_t **fork_high);
void				perform_eating(t_philo *philo, pthread_mutex_t *fork_low,
						pthread_mutex_t *fork_high);

void				*monitor(void *arg);
int					check_loop(t_rules *rules);
int					philo_dead(t_philo *philo, int time_to_die);
int					who_is_dead(t_rules *rules);
int					all_eaten(t_rules *rules);
int					has_philo_finished(t_philo *philo, int min_meals);
void				perform_eating(t_philo *philo, pthread_mutex_t *fl,
						pthread_mutex_t *fh);

#endif