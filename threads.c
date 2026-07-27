/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:44:58 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/27 15:45:14 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include <time.h>

t_coder	*coder_creation(t_input *input)
{
	t_coder	*coders;
	int		i; 

	i = 0;
	coders = malloc(sizeof(t_coder) * input->coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < input->coders)
	{
		coders[i].index = i + 1;
		coders[i].limits = input;
		coders[i].total_compiles = 0;
		coders[i].last_compile_timestamp = 0;
		pthread_mutex_init(&coders[i].mutex, NULL);
		i++;
	}
	return (coders);
}

void	*start_thread(void *arg)
{
	//t_coder	*data;
	sys *data;
	int	n;

	data = arg;
	n = 0;
	pthread_t		thisThread = pthread_self();
	printf("Created a new thread: [%lu]\n", (unsigned long)thisThread);
	while(n < 5)
	{
		pthread_mutex_lock(&data->mutex);
		printf("Coder : %d\n", data->couter++);
		n++;
		usleep(100000);
		pthread_mutex_unlock(&data->mutex);
	}	
	pthread_exit(NULL);
	return (arg);
}