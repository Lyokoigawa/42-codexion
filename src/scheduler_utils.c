/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   scheduler_utils.c                                 :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/09 02:40:55 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:47 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	consume_dongles(t_request *request)
{
	lock_dongles(request->coder);
	request->coder->l_dong->in_use = 1;
	request->coder->r_dong->in_use = 1;
	unlock_dongles(request->coder);
}

void	queue_request(t_simulation *sim, t_request *to_queue)
{
	sim->scheduler.queue[sim->scheduler.queue_size] = to_queue;
	sim->scheduler.queue_size++;
	heap_pop(sim);
}

void	restore_queue(t_simulation *sim)
{
	while (sim->scheduler.queue_size > 0)
	{
		sim->scheduler.queue_size--;
		heap_push(sim, sim->scheduler.queue[sim->scheduler.queue_size]);
		sim->scheduler.queue[sim->scheduler.queue_size] = NULL;
	}
}

int	dongle_available(t_dongle *dongle, t_simulation *sim)
{
	long	now;

	now = elapsed_time(sim->start_time);
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->in_use)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	if (now - dongle->cooldown_start < sim->input->cooldown)
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (1);
}
