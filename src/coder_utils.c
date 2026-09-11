/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_utils.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/06 18:11:53 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:33:24 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	update_last_compile(t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_timestamp = elapsed_time(coder->sim->start_time);
	pthread_mutex_unlock(&coder->mutex);
}

void	lock_dongles(t_coder *coder)
{
	if (coder->l_dong->index < coder->r_dong->index)
	{
		pthread_mutex_lock(&coder->l_dong->mutex);
		if (coder->l_dong != coder->r_dong)
			pthread_mutex_lock(&coder->r_dong->mutex);
	}
	else
	{
		pthread_mutex_lock(&coder->r_dong->mutex);
		if (coder->l_dong != coder->r_dong)
			pthread_mutex_lock(&coder->l_dong->mutex);
	}
}

void	unlock_dongles(t_coder *coder)
{
	if (coder->l_dong != coder->r_dong)
		pthread_mutex_unlock(&coder->r_dong->mutex);
	pthread_mutex_unlock(&coder->l_dong->mutex);
}

void	coder_sleep(t_coder *coder, long time_to_wait)
{
	long	deadline;
	long	task_time;

	deadline = (coder->last_compile_timestamp + coder->sim->input->burn);
	task_time = (elapsed_time(coder->sim->start_time) + time_to_wait);
	while (simulation_running(coder->sim))
	{
		if (elapsed_time(coder->sim->start_time) >= deadline)
			return ;
		if (elapsed_time(coder->sim->start_time )>= task_time)
			return ;
		usleep(1000);
	}
}
