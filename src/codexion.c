/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/19 13:42:28 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:20 by username        ###   ########.fr        */
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
