/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:14:59 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/06/15 15:46:27 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	check_scheduler(char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
		return (1);
	else if (strcmp(scheduler, "edf") == 0)
		return (2);
	else
		return (0);
}

int	validate_input(char **in)
{
	int	i[2];

	i[0] = 0;
	i[1] = 1;
	while (in[i[1]])
	{
		while(i[1] <= 9)
		{
			if (in[i[1]][i[0]] < '0' || in[i[1]][i[0]] > '9')
				return (0);
			i[0]++;
		}
		i[1]++;
		i[0] = 0;
	}
	return (1);
}

t_input	*input_parse(char **in)
{
	t_input	*out;

	out = malloc(sizeof(t_input));
	if (!out)
		return (NULL);
	if (!validate_input(in))
		return (NULL);
	out->coders = atoi(in[1]);
	out->burn = atoi(in[2]);
	out->compile = atoi(in[3]);
	out->debug = atoi(in[4]);
	out->refactor = atoi(in[5]);
	out->target = atoi(in[6]);
	out->cooldown = atoi(in[7]);
	out->scheduler = check_scheduler(in[8]);
	if (out->scheduler == 0)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
