/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 14:09:25 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/04 14:42:15 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	codex_comp(t_coder coder)
{
	if (coder.l_dong->is_ready && coder.r_dong->is_ready)
	{
		pthread_mutex_lock(&coder.l_dong->mutex);
		pthread_mutex_lock(&coder.r_dong->mutex);
		usleep(coder.limits->compile * 1000);
		printf("Coder [%d] has compiled\n", coder.index);
		pthread_mutex_unlock(&coder.l_dong->mutex);
		pthread_mutex_unlock(&coder.r_dong->mutex);
	}
}

void	codex_debug(t_coder coder)
{
	usleep(coder.limits->debug * 1000);
	printf("Coder [%d] has debugged\n", coder.index);
}

void	codex_refac(t_coder coder)
{
	usleep(coder.limits->refactor * 1000);
	coder.total_compiles += 1;
	printf("Coder [%d] has refactored\n", coder.index);
}
