/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   heap.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/08 17:25:35 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:34 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	heapify_up(t_heap *heap, int index, int policy)
{
	int			parent_index;
	t_request	*temp;

	if (index == 0)
		return ;
	parent_index = (index - 1) / 2;
	if (!is_higher(heap->request[index], heap->request[parent_index], policy))
		return ;
	temp = heap->request[index];
	heap->request[index] = heap->request[parent_index];
	heap->request[parent_index] = temp;
	heapify_up(heap, parent_index, policy);
}

void	heapify_down(t_heap *heap, int index, int policy)
{
	int			left_child_index;
	int			right_child_index;
	int			smallest_index;
	t_request	*temp;

	left_child_index = 2 * index + 1;
	right_child_index = 2 * index + 2;
	if (left_child_index >= heap->size)
		return ;
	smallest_index = index;
	if (left_child_index < heap->size)
		smallest_index = higher_child(heap, left_child_index, right_child_index,
				policy);
	if (is_higher(heap->request[smallest_index], heap->request[index], policy))
	{
		temp = heap->request[index];
		heap->request[index] = heap->request[smallest_index];
		heap->request[smallest_index] = temp;
		heapify_down(heap, smallest_index, policy);
	}
}

void	heap_push(t_simulation *sim, t_request *request)
{
	t_heap	*heap;

	if (!request)
		return ;
	heap = sim->scheduler.heap;
	if (heap->size >= heap->capacity)
		return ;
	heap->request[heap->size] = request;
	heap->size++;
	heapify_up(heap, heap->size - 1, sim->input->scheduler);
}

void	heap_pop(t_simulation *sim)
{
	t_heap	*heap;

	heap = sim->scheduler.heap;
	if (!heap || heap->size == 0)
		return ;
	heap->request[0] = heap->request[heap->size - 1];
	heap->size--;
	heapify_down(heap, 0, sim->input->scheduler);
}

t_request	*heap_peek(t_simulation *sim)
{
	return (sim->scheduler.heap->request[0]);
}
