/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 02:40:55 by marvin            #+#    #+#             */
/*   Updated: 2026/08/09 02:40:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    consume_dongles(t_request *request)
{
    lock_dongles(request->coder);
    request->coder->l_dong->in_use = 1;
    request->coder->r_dong->in_use = 1;
    unlock_dongles(request->coder);
}

void    queue_request(t_simulation *sim, t_request *to_queue)
{
    sim->scheduler.queue[sim->scheduler.queue_size] = to_queue;
    sim->scheduler.queue_size++;
    heap_pop(sim);
}

void    restore_queue(t_simulation *sim)
{
    while (sim->scheduler.queue_size > 0)
    {
        heap_push(sim, sim->scheduler.queue[sim->scheduler.queue_size - 1]);
        sim->scheduler.queue[sim->scheduler.queue_size] = NULL;
        sim->scheduler.queue_size--;
    }
}

int dongle_available(t_dongle *dongle, t_simulation *sim)
{
    long    now;

    now = elapsed_time(sim->start_time);
    if (dongle->in_use)
        return (0);
    if (now - dongle->cooldown_start < sim->input->cooldown)
        return (0);
    return (1);
}
