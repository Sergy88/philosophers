/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 01:06:12 by Sergey            #+#    #+#             */
/*   Updated: 2021/12/06 21:39:45 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

int	get_stamp(t_phil_state *p_phil)
{
	return (get_time() - p_phil->start_t);
}

int	eat(t_phil_state *p_phil)
{
	pthread_mutex_lock(&p_phil->forks[p_phil->pos]);
	printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, p_phil->pos + 1);
	pthread_mutex_lock(&p_phil->forks[(p_phil->pos + 2) % p_phil->phils_total]);
	if (update_status(p_phil))
	{
		printf("Philo #%d, has taken fork %d\n", p_phil->pos + 1, ((p_phil->pos + 2) % p_phil->phils_total));
		atomic_status_prntr(MESSAGE_EAT, get_stamp(p_phil), p_phil->pos + 1);
	}
	pthread_mutex_unlock(&p_phil->forks[p_phil->pos]);
	pthread_mutex_unlock(&p_phil->forks[(p_phil->pos + 1) % p_phil->phils_total]);
	return (1);
}