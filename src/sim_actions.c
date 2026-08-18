/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:06:58 by marvin            #+#    #+#             */
/*   Updated: 2026/08/06 19:06:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    end_simulation(t_simulation *sim)
{
    int i;

    i = 0;
    pthread_mutex_lock(&sim->state_mutex);
    sim->running = 0;
    while (i < sim->input->coders)
    {
        pthread_cond_broadcast(&sim->coders[i].cond);
        i++;
    }
    pthread_mutex_unlock(&sim->state_mutex);
}

int simulation_running(t_simulation *sim)
{
    int running;

    pthread_mutex_lock(&sim->state_mutex);
    running = sim->running;
    pthread_mutex_unlock(&sim->state_mutex);
    return (running);
}

int simulation_complete(t_simulation *sim)
{
    int i;

    i = 0;
    while (i < sim->input->coders)
    {
        if (sim->coders[i].total_compiles < sim->input->target)
            return (0);
        i++;
    }
    return (1);
}

int burned_out(t_simulation *sim)
{
    int i;
    long    deadline;

    i = 0;
    while (i < sim->input->coders)
    {
        deadline = sim->coders[i].last_compile_timestamp + sim->input->burn;
        if (elapsed_time(sim->start_time) > deadline)
        {
            print_status(&sim->coders[i], "has burned out");    
            return (1);
        }
        i++;
    }
    return (0);
}

void    sim_run(t_simulation *sim)
{
    usleep(1000);
    while (simulation_running(sim))
    {
        if (burned_out(sim))
            end_simulation(sim);
        if (simulation_complete(sim))
            end_simulation(sim);
        check_request(sim);
        ft_usleep(1, sim);
    }
}
