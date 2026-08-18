/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_spawner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 15:35:29 by marvin            #+#    #+#             */
/*   Updated: 2026/08/16 15:35:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_simulation    *spawn_world(t_input *in)
{
    t_simulation    *sim;

    sim = simulation_creation(in);
    if (!sim)
    {
        free(in);
        return (NULL);
    }
    return (sim);
}

void    run_world(t_simulation *sim)
{
    int i;
    
    i = 0;
    while (i < sim->input->coders)
	{
        pthread_create(&sim->coders[i].thread, NULL, start_thread, &sim->coders[i]);
		i++;
	}
	pthread_create(&sim->monitor, NULL, sim_start, sim);
}

void    kill_world(t_simulation *sim)
{
    int i;

	i = 0;
	while (i < sim->input->coders)
        pthread_join(sim->coders[i++].thread, NULL);
	pthread_join(sim->monitor, NULL);
	destroy_simulation(sim);
}
