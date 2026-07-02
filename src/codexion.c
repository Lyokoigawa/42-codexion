/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:42:28 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/02 14:20:39 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int ac, char **av)
{
	t_input		*output;
	int			i;
	pthread_t	*threads;
	t_coder		**coders;

	i = 0;
	output = NULL;
	if (ac == 9)
	{
		output = input_parse(av);
		if (!output)
			return (0);
		threads = malloc(sizeof(pthread_t) * output->coders);
		if (!threads)
		{
			free(output);
			return (0);
		}
		coders = coder_creation(output);
		if (!coders)
		{
			free(output);
			free(threads);
			return (0);
		}
		while (i < output->coders)
		{
			printf("slot [%d]: created\n", i);
			pthread_create(&threads[i], NULL, start_thread, &coders[i]);
			i++;
		}
		i = 0;
		while (i < output->coders)
			pthread_join(threads[i++], NULL);
		free(output);
		free(threads);
	}
	else
		printf("Not enough inputs\nRecieved: %d\nExpected: 9", ac);
}
