/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:42:28 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/16 16:06:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	main(int ac, char **av)
{
	t_input			*output;
	t_simulation	*sim;

	sim = NULL;
	if (ac != 9)
	{
		printf("ERROR: wrong input count\nRecieved: %d\nExpected: 9\n", ac);
		return (0);
	}
	output = input_parse(av);
	if (!output)
		return (0);
	sim = spawn_world(output);
	if (!sim)
		return (0);
	run_world(sim);
	kill_world(sim);
	free(output);
	return (0);
}
