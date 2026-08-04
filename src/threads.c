/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:44:58 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/04 14:41:35 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_monitor	monitor_creation(t_input *input, t_coder *coders)
{
	t_monitor	monitor;

	monitor.coders = coders;
	monitor.input = input;
	monitor.total_compiles = 0;
	pthread_mutex_init(&monitor.print_mutex, NULL);
	return (monitor);
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
		dongles[i].is_available = 1;
		dongles[i].is_ready = 1;
		dongles[i].cooldown_timestamp = 0;
		pthread_mutex_init(&dongles[i].mutex, NULL);
		i++;
	}
	return (dongles);
}

t_coder	*coder_creation(t_input *input)
{
	t_coder		*coders;
	t_dongle	*dongles;
	int			i; 

	i = 0;
	dongles = dongle_creation(input);
	coders = malloc(sizeof(t_coder) * input->coders);
	if (!coders || !dongles)
		return (NULL);
	while (i < input->coders)
	{
		coders[i].index = i + 1;
		coders[i].limits = input;
		coders[i].total_compiles = 0;
		coders[i].last_compile_timestamp = 0;
		coders[i].l_dong = &dongles[i];
		if (i == input->coders - 1)
			coders[i].r_dong = &dongles[0];
		else
			coders[i].r_dong = &dongles[i + 1];
		pthread_mutex_init(&coders[i].mutex, NULL);
		pthread_create(&coders[i].thread, NULL, start_thread, &coders[i]);
		i++;
	}
	return (coders);
}

void	*start_thread(void *arg)
{
	t_coder			*data;

	data = arg;
	printf("Coder index: %d\n", data->index);
	printf("Dongles nearby: %d, %d\n", data->l_dong->index, data->r_dong->index);
	while (data->total_compiles < data->limits->target)
	{
		codex_comp(*data);
		codex_debug(*data);
		codex_refac(*data);
		printf("Current number of compiles %d - Coder [%d]\n", data->total_compiles, data->index);
	}
	pthread_exit(NULL);
	return (arg);
}