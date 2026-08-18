/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   heap_utils.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/12 17:21:20 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:41 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	higher_child(t_heap *heap, int left_index, int right_index, int policy)
{
	if (right_index >= heap->size)
		return (left_index);
	if (is_higher(heap->request[left_index], heap->request[right_index],
			policy))
		return (left_index);
	return (right_index);
}

int	is_higher(t_request *a, t_request *b, int policy)
{
	if (policy == 1)
	{
		if (a->timestamp == b->timestamp)
			return (a->coder->index < b->coder->index);
		else
			return (a->timestamp < b->timestamp);
	}
	else if (policy == 2)
	{
		if (a->deadline == b->deadline)
			return (a->coder->index < b->coder->index);
		else
			return (a->deadline < b->deadline);
	}
	return (a->coder->index < b->coder->index);
}
