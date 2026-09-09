/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   sim_actions.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/06 19:06:58 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:53 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	end_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->state_mutex);
	sim->running = 0;
	pthread_mutex_unlock(&sim->state_mutex);
	while (i < sim->input->coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		pthread_cond_broadcast(&sim->coders[i].cond);
		pthread_mutex_unlock(&sim->coders[i].mutex);
		i++;
	}
}

int	simulation_running(t_simulation *sim)
{
	int	running;

	pthread_mutex_lock(&sim->state_mutex);
	running = sim->running;
	pthread_mutex_unlock(&sim->state_mutex);
	return (running);
}

int	simulation_complete(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->input->coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		if (sim->coders[i].total_compiles < sim->input->target)
		{
			pthread_mutex_unlock(&sim->coders[i].mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->coders[i].mutex);
		i++;
	}
	return (1);
}

int	burned_out(t_simulation *sim)
{
	int		i;
	long	deadline;
	//long	time_now;

	i = 0;
	while (i < sim->input->coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		//time_now = get_current_time() - sim->coders[i].last_compile_timestamp;
		deadline = sim->coders[i].last_compile_timestamp + sim->input->burn;
		//printf("Time to burn: %ld ", time_now);
		//printf("Deadline: %ld ", deadline);
		//printf("Elapsed time: %ld\n", elapsed_time(sim->start_time));
		pthread_mutex_unlock(&sim->coders[i].mutex);
		if (elapsed_time(sim->start_time) > deadline)
		{
			print_status(&sim->coders[i], "has burned out");
			return (1);
		}
		i++;
	}
	return (0);
}

void	sim_run(t_simulation *sim)
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
