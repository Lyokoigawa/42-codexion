/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 17:21:20 by marvin            #+#    #+#             */
/*   Updated: 2026/08/12 17:21:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int higher_child(t_heap *heap, int left_index, int right_index, int policy)
{
    if (right_index >= heap->size)
        return (left_index);
    if (is_higher(heap->request[left_index], heap->request[right_index], policy))
        return (left_index);
    return (right_index);
}

int is_higher(t_request *a, t_request *b, int policy)
{
    if (policy == 1) // FIFO
    {
        if (a->timestamp == b->timestamp)
            return (a->coder->index < b->coder->index); // Tiebreaker by coder index
        else
            return (a->timestamp < b->timestamp);
    }
    else if (policy == 2) // EDF
    {
        if (a->deadline == b->deadline)
            return (a->coder->index < b->coder->index); // Tiebreaker by coder index
        else
            return (a->deadline < b->deadline);
    }
    return (a->coder->index < b->coder->index); // For RR, we can use arrival time as a tiebreaker
}
