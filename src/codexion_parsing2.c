/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion_parsing2.c                               :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/08/16 14:14:36 by username         #+#    #+#              */
/*   Updated: 2026/08/18 13:57:07 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	individual_input_check(int *in)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (in[i++] >= in[0])
		{
			individual_input_error(--i);
			return (0);
		}
	}
	return (1);
}
