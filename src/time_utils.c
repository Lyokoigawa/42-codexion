/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 12:03:02 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/13 23:43:23 by marvin           ###   ########.fr       */
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

int	ft_usleep(long miliseconds, t_simulation *monitor)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
	{
		if (monitor->running == 0)
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

void		get_deadline(struct timespec *ts, long wait_ms)
{
    struct timeval  now;
    long            total_nsec;

    gettimeofday(&now, NULL);
    ts->tv_sec = now.tv_sec;
    ts->tv_nsec = now.tv_usec * 1000;      // microseconds -> nanoseconds
    total_nsec = ts->tv_nsec + (wait_ms * 1000000L);  // add your wait, in nanoseconds
    ts->tv_sec += total_nsec / 1000000000L;   // carry any overflow into seconds
    ts->tv_nsec = total_nsec % 1000000000L;   // remainder stays as nanoseconds
}
