/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_parsing2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 14:14:36 by marvin            #+#    #+#             */
/*   Updated: 2026/08/16 14:14:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int individual_input_check(int *in)
{
    int i;

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
