/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 01:37:57 by marvin            #+#    #+#             */
/*   Updated: 2026/08/16 01:37:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_scheduler(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->scheduler.heap->size)
		free(sim->scheduler.heap->request[i++]);
	free(sim->scheduler.heap->request);
	free(sim->scheduler.heap);
	i = 0;
	while (i < sim->scheduler.queue_size)
		free(sim->scheduler.queue[i++]);
	free(sim->scheduler.queue);
	pthread_mutex_destroy(&sim->scheduler.mutex);
	pthread_cond_destroy(&sim->scheduler.cond);
}

void	destroy_dongles(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->coders)
		pthread_mutex_destroy(&sim->dongles[i++].mutex);
	free(sim->dongles);
}

void	destroy_coders(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->coders)
	{
		pthread_mutex_destroy(&sim->coders[i].mutex);
		pthread_cond_destroy(&sim->coders[i].cond);
		i++;
	}
	free(sim->coders);
}

void	destroy_simulation(t_simulation *sim)
{
	destroy_scheduler(sim);
	destroy_dongles(sim);
	destroy_coders(sim);
	pthread_mutex_destroy(&sim->start_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
	pthread_cond_destroy(&sim->start_cond);
	free(sim);
}
