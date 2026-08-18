/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 18:11:53 by marvin            #+#    #+#             */
/*   Updated: 2026/08/06 18:11:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void    update_last_compile(t_coder *coder)
{
    pthread_mutex_lock(&coder->mutex);
    coder->last_compile_timestamp = elapsed_time(coder->sim->start_time);
    pthread_mutex_unlock(&coder->mutex);
}

void    lock_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->l_dong->mutex);
    if (coder->l_dong != coder->r_dong)
        pthread_mutex_lock(&coder->r_dong->mutex);
}

void    unlock_dongles(t_coder *coder)
{
    if (coder->l_dong != coder->r_dong)
        pthread_mutex_unlock(&coder->r_dong->mutex);
    pthread_mutex_unlock(&coder->l_dong->mutex);
}
