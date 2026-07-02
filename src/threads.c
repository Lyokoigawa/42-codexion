/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:44:58 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/02 14:32:43 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	**coder_creation(t_input *input)
{
	t_coder	**coders;
	int		i; 

	i = 0;
	coders = malloc(sizeof(t_coder *) * input->coders);
	if (!coders)
		return (NULL);
	while (i < input->coders)
	{
		coders[i++] = malloc(sizeof(t_coder));
		if (!coders[i])
		{
			while (--i >= 0)
				free(coders[i]);
			free(coders);
			return (NULL);
		}
	}
	i = 0;
	while (i++ < input->coders)
	{
		coders[i]->index = i + 1;
		coders[i]->limits = input;
		coders[i]->total_compiles = 0;
		coders[i]->last_compile_timestamp = 0;
	}
	return (coders);
}

void	*start_thread(void *arg)
{
	t_coder	*data;

	data = arg;
	pthread_t	thisThread = pthread_self();
	printf("Created a new thread: [%lu]\n", (unsigned long)thisThread);
	printf("Time to burnout: %d\n", data->limits->burn);
	pthread_exit(NULL);
	return (arg);
}
