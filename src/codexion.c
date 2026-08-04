/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:42:28 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/04 13:52:33 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int ac, char **av)
{
	t_input		*output;
	int			i;
	t_coder		*coders;

	i = 0;
	output = NULL;
	if (ac == 9)
	{
		output = input_parse(av);
		if (!output)
			return (0);
		coders = coder_creation(output);
		if (!coders)
		{
			free(output);
			return (0);
		}
		while (i < output->coders)
		{
			printf("slot [%d]: created\n", i);
			pthread_create(&coders[i].thread, NULL, start_thread, &coders[i]);
			i++;
		}
		i = 0;
		while (i < output->coders)
			pthread_join(coders[i++].thread, NULL);
		free(output);
	}
	else
		printf("Not enough inputs\nRecieved: %d\nExpected: 9", ac);
}
