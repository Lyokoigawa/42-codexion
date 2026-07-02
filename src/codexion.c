/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:42:28 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/02 11:06:55 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int ac, char **av)
{
	t_input		*output;
	int			i;
	pthread_t	thread1;

	i = 0;
	output = NULL;
	if (ac == 9)
	{
		output = input_parse(av);
		if (!output)
		{
			printf("Oops.\n");
			return (0);
		}
		while (i < output->coders)
		{
			printf("slot [%d]: created\n", i);
			pthread_create(&thread1, NULL, start_thread, NULL);
			i++;
		}
		free(output);
	}
	else
		printf("Not enough inputs\nRecieved: %d\nExpected: 9", ac);
}
