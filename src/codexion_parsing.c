/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 10:14:59 by username          #+#    #+#             */
/*   Updated: 2026/09/11 13:17:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	is_possible(char **in)
{
	int	nums[5];

	nums[0] = atoi(in[2]);
	nums[1] = atoi(in[3]);
	nums[2] = atoi(in[4]);
	nums[3] = atoi(in[5]);
	nums[4] = atoi(in[7]);
	individual_input_check(nums);
	if ((nums[1] + nums[2] + nums[3]) >= nums[0])
	{
		feasibility_error(1);
	}
	else if ((nums[1] + nums[4]) >= nums[0])
	{
		feasibility_error(2);
	}
	return (1);
}

int	check_inputs(char **in)
{
	int	i;

	i = 1;
	if (atoi(in[i]) <= 0)
		input_error(i);
	i++;
	while (i < 8)
	{
		if (atoi(in[i]) < 0)
		{
			input_error(i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_scheduler(char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
		return (1);
	else if (strcmp(scheduler, "edf") == 0)
		return (2);
	else
	{
		printf("ERROR: input must be either 'fifo' or 'edf'\n");
		return (0);
	}
}

int	validate_input(char **in)
{
	int	i[2];

	i[0] = 0;
	i[1] = 1;
	while (in[i[1]])
	{
		while (in[i[1]][i[0]] && i[1] < 8)
		{
			if (!(in[i[1]][i[0]] >= '0' && in[i[1]][i[0]] <= '9'))
			{
				input_error(i[1]);
				return (0);
			}
			i[0]++;
		}
		i[1]++;
		i[0] = 0;
	}
	if (!check_inputs(in))
		return (0);
	if (!is_possible(in))
		return (0);
	return (1);
}

t_input	*input_parse(char **in)
{
	t_input	*out;

	if (!validate_input(in))
		return (NULL);
	out = malloc(sizeof(t_input));
	if (!out)
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
