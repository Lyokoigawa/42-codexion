/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_schedule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 16:11:41 by marvin            #+#    #+#             */
/*   Updated: 2026/08/08 16:11:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    init_heap(t_heap *heap, int capacity)
{
    heap->request = malloc(sizeof(t_request *) * capacity);
    if (!heap->request)
        return ;
    heap->size = 0;
    heap->capacity = capacity;
}

void    init_scheduler(t_simulation *sim, t_heap *heap)
{
    sim->scheduler.queue = malloc(sizeof(t_request *) * sim->input->coders);
    if (!sim->scheduler.queue)
        return ;
    sim->scheduler.queue_size = 0;
    sim->scheduler.heap = heap;
    pthread_mutex_init(&sim->scheduler.mutex, NULL);
    pthread_cond_init(&sim->scheduler.cond, NULL);  
}

int can_fulfill(t_request *request, t_simulation *sim)
{
    if (dongle_available(request->coder->l_dong, sim) && dongle_available(request->coder->r_dong, sim))
        return (1);
    return (0);
}

void    check_request(t_simulation *sim)
{
    t_request       *request;
    struct timespec ts;

    pthread_mutex_lock(&sim->scheduler.mutex);
    while (sim->scheduler.heap->size == 0 && simulation_running(sim))
    {
        get_deadline(&ts, 5);
        pthread_cond_timedwait(&sim->scheduler.cond, &sim->scheduler.mutex, &ts);
    }
    if (!simulation_running(sim))
    {
        pthread_mutex_unlock(&sim->scheduler.mutex);
        return ;
    }
    while (sim->scheduler.heap->size > 0)
    {
        request = heap_peek(sim);
        if (can_fulfill(request, sim))
            accept_request(sim, request);
        else
            queue_request(sim, request);
    }
    restore_queue(sim);
    pthread_mutex_unlock(&sim->scheduler.mutex);
}

void    accept_request(t_simulation *sim, t_request *request)
{
    heap_pop(sim);
    consume_dongles(request);
    pthread_mutex_lock(&request->coder->mutex);
    request->coder->can_compile = 1;
    pthread_cond_signal(&request->coder->cond);
    pthread_mutex_unlock(&request->coder->mutex);
    free(request);
}
