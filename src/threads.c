/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:44:58 by username          #+#    #+#             */
/*   Updated: 2026/09/09 13:53:31 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_simulation	*simulation_creation(t_input *input)
{
	t_simulation	*sim;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->input = input;
	sim->dongles = dongle_creation(sim->input);
	sim->coders = coder_creation(sim);
	sim->running = 0;
	sim->start = 0;
	sim->start_time = get_current_time();
	sim->scheduler.heap = malloc(sizeof(t_heap));
	if (!sim->scheduler.heap)
		return (NULL);
	init_heap(sim->scheduler.heap, sim->input->coders);
	init_scheduler(sim, sim->scheduler.heap);
	pthread_mutex_init(&sim->start_mutex, NULL);
	pthread_mutex_init(&sim->print_mutex, NULL);
	pthread_mutex_init(&sim->state_mutex, NULL);
	pthread_cond_init(&sim->start_cond, NULL);
	return (sim);
}

t_dongle	*dongle_creation(t_input *input)
{
	t_dongle	*dongles;
	int			i;

	i = 0;
	dongles = malloc(sizeof(t_dongle) * input->coders);
	if (!dongles)
		return (NULL);
	while (i < input->coders)
	{
		dongles[i].index = i + 1;
		dongles[i].is_ready = 1;
		dongles[i].in_use = 0;
		dongles[i].cooldown_start = -input->cooldown;
		pthread_mutex_init(&dongles[i].mutex, NULL);
		dongles[i].heap = NULL;
		i++;
	}
	return (dongles);
}

t_coder	*coder_creation(t_simulation *sim)
{
	t_coder	*coders;
	int		i;

	i = 0;
	coders = malloc(sizeof(t_coder) * sim->input->coders);
	if (!coders || !sim->dongles)
		return (NULL);
	while (i < sim->input->coders)
	{
		coders[i].index = i + 1;
		coders[i].sim = sim;
		coders[i].total_compiles = 0;
		coders[i].last_compile_timestamp = 0;
		coders[i].can_compile = 0;
		coders[i].l_dong = &sim->dongles[i];
		if (i == sim->input->coders - 1)
			coders[i].r_dong = &sim->dongles[0];
		else
			coders[i].r_dong = &sim->dongles[i + 1];
		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_cond_init(&coders[i].cond, NULL);
		i++;
	}
	return (coders);
}

void	*sim_start(void *arg)
{
	t_simulation	*sim;

	sim = arg;
	pthread_mutex_lock(&sim->start_mutex);
	sim->start = 1;
	sim->running = 1;
	pthread_cond_broadcast(&sim->start_cond);
	pthread_mutex_unlock(&sim->start_mutex);
	sim_run(sim);
	return (arg);
}

void	*start_thread(void *arg)
{
	t_coder	*data;

	data = arg;
	pthread_mutex_lock(&data->sim->start_mutex);
	while (!simulation_running(data->sim))
		pthread_cond_wait(&data->sim->start_cond, &data->sim->start_mutex);
	pthread_mutex_unlock(&data->sim->start_mutex);
	while (simulation_running(data->sim))
	{
		coder_request(data);
		pthread_mutex_lock(&data->mutex);
		if (!data->can_compile && simulation_running(data->sim))
			pthread_cond_wait(&data->cond, &data->mutex);
		data->can_compile = 0;
		pthread_mutex_unlock(&data->mutex);
		codex_comp(data);
		codex_debug(data);
		codex_refac(data);
	}
	pthread_exit(NULL);
	return (arg);
}
