/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 12:03:02 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/04 12:05:20 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (fprintf(stderr, "ERROR: gettimeofday() failed.\n"), -1);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
}

int	ft_usleep(long miliseconds, t_monitor *monitor)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
	{
		if (simulation_finished(monitor))
			break ;
		usleep(500);
	}
	return (0);
}

void	ft_sleep_ms(long ms)
{
	struct timespec	ts;

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1e6;
	nanosleep(&ts, NULL);
}

long	elapsed_time(long start)
{
	return ((long)get_current_time() - start);
}
