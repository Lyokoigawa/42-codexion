/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   errors.c                                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/15 19:38:34 by username         #+#    #+#              */
/*   Updated: 2026/08/18 14:00:01 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	individual_input_error(int error)
{
	if (error == 1)
		printf("WARNING: time_to_compile exceeds burnout_time\n");
	else if (error == 2)
		printf("WARNING: time_to_debug exceeds burnout_time\n");
	else if (error == 3)
		printf("WARNING: time_to_refactor exceeds burnout_time\n");
	else if (error == 4)
		printf("WARNING: cooldown_time exceeds burnout_time\n");
	printf("Simulation will be impossible.\n");
}

void	feasibility_error(int error)
{
	if (error == 1)
		printf("WARNING: time_to_compile + time_to_debug +%s",
			" time_to_refactor exceeds burnout_time.\n");
	else if (error == 2)
		printf("WARNING: time_to_compile + cooldown_time %s",
			"exceeds burnout_time.\n");
	printf("Simulation will be impossible.\n");
}

void	input_error(int i)
{
	char	*errors[7];

	errors[0] = "max coders";
	errors[1] = "burnout time";
	errors[2] = "compile time";
	errors[3] = "debug time";
	errors[4] = "refactor time";
	errors[5] = "total compiles";
	errors[6] = "dongle cooldown";
	printf("ERROR: %s must be a positive integer.\n", errors[i - 1]);
}
