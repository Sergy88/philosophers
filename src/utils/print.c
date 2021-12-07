/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:57:05 by Sergey            #+#    #+#             */
/*   Updated: 2021/11/30 00:37:28 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	atomic_status_prntr(char *message, unsigned long time_stamp, int phil_num)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	printf("%d %d %s\n", time_stamp, phil_num, message);
	pthread_mutex_unlock(&print_mutex);
}