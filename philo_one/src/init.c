/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:31:47 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/12 13:48:07 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static pthread_mutex_t	*forks_init(int n)
{
	int				c;
	pthread_mutex_t	*forks;

	c = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n); //todo check alloc
	while (c < n)
		pthread_mutex_init(&forks[c++], NULL);
	return forks;
}

static int	init_philos(t_phil_state **phil_st[], int params[])
{
	int				c;
	pthread_mutex_t	*forks;

	forks = forks_init(params[num_philo]);
	*phil_st = malloc(sizeof(t_phil_state *) * params[num_philo]); //todo check alloc
	c = 0;
	while (c < params[num_philo])
	{
		(*phil_st)[c] = malloc(sizeof(t_phil_state)); //todo check alloc and free
		(*phil_st)[c]->phils_total = params[num_philo];
		(*phil_st)[c]->forks = forks;
		(*phil_st)[c]->pos = c;
		(*phil_st)[c]->time_to_die = params[time_to_die];
		(*phil_st)[c]->time_to_eat = params[time_to_eat];
		(*phil_st)[c]->time_to_sleep = params[time_to_sleep];
		(*phil_st)[c]->is_alive = 1;
		if (params[num_to_eat] == 0)
			(*phil_st)[c]->eat_forever = 1;
		else
			(*phil_st)[c]->num_to_eat = params[num_to_eat];
		(*phil_st)[c]->should_sleep = 0;
		(*phil_st)[c]->can_b_free = 0;
		c++;
	}
	return (1);
}

int	init_state_mtx(t_phil_state *phils[], int c)
{
	int					i;
	pthread_mutex_t		*p_state_mtx;

	i = 0;
	p_state_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(p_state_mtx))
		return (0);
	pthread_mutex_init(p_state_mtx, NULL);
	while (i < c)
		phils[i++]->state_mtx = p_state_mtx; //todo malloc
	return (1);
}

int	init(int argc, char *argv[], t_phil_state **phil_st[])
{
	int	params[NUM_PARAM];

	if (argc < 5 || argc > 6)
		return (exit_fail("Invalid args.\n", -1));
	params[num_to_eat] = 0;
	params[num_philo] = ft_atoi(argv[1]);
	params[time_to_die] = ft_atoi(argv[2]);
	params[time_to_eat] = ft_atoi(argv[3]);
	params[time_to_sleep] = ft_atoi(argv[4]);
	if (argc == 6)
		params[num_to_eat] = ft_atoi(argv[5]);
	init_philos(phil_st, params);
	init_state_mtx(*phil_st, params[num_philo]);
	return (1);
}