/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:09:25 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/15 18:57:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	print_status(t_coder *coder, const char *action)
{
	pthread_mutex_lock(&coder->sim->print_mutex);
	if (simulation_running(coder->sim))
		printf("%ld Coder [%d] %s\n", elapsed_time(coder->sim->start_time), coder->index, action);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}

void	coder_request(t_coder *coder)
{
	t_request	*request;

	request = malloc(sizeof(t_request));
	if (!request)
		return ;
	request->coder = coder;
	request->timestamp = elapsed_time(coder->sim->start_time);
	request->deadline = coder->last_compile_timestamp + coder->sim->input->burn;
	pthread_mutex_lock(&coder->sim->scheduler.mutex);
	heap_push(coder->sim, request);
	pthread_cond_broadcast(&coder->sim->scheduler.cond);
	pthread_mutex_unlock(&coder->sim->scheduler.mutex);
}

int	codex_comp(t_coder *coder)
{
	lock_dongles(coder);
	print_status(coder, "has picked up a dongle");
	print_status(coder, "has picked up a dongle");
	if (simulation_running(coder->sim))
	{
		print_status(coder, "is compiling");
		update_last_compile(coder);
		usleep(coder->sim->input->compile * 1000);
		coder->l_dong->in_use = 0;
		coder->r_dong->in_use = 0;
		coder->l_dong->cooldown_start = elapsed_time(coder->sim->start_time);
		coder->r_dong->cooldown_start = elapsed_time(coder->sim->start_time);
	}
	unlock_dongles(coder);
	pthread_mutex_lock(&coder->sim->scheduler.mutex);
	pthread_cond_signal(&coder->sim->scheduler.cond);
	pthread_mutex_unlock(&coder->sim->scheduler.mutex);
	return (1);
}

int	codex_debug(t_coder *coder)
{
	if (!simulation_running(coder->sim))
		return (0);
	print_status(coder, "is debugging");
	usleep(coder->sim->input->debug * 1000);
	return (1);
}

int	codex_refac(t_coder *coder)
{
	if (!simulation_running(coder->sim))
		return (0);
	print_status(coder, "is refactoring");
	usleep(coder->sim->input->refactor * 1000);
	pthread_mutex_lock(&coder->mutex);
	coder->total_compiles += 1;
	pthread_mutex_unlock(&coder->mutex);
	return (1);	
}
