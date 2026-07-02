/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:22:00 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/02 10:57:23 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef	struct input
{
	int	coders; //number of coders
	int	burn; //time to burnout
	int	compile; //time to compile
	int	debug; //time to debug
	int	refactor; //time to refactor
	int	target; //target compiles
	int	cooldown; //dongle cooldown
	int	scheduler; //fifo or edf?
}		t_input;

typedef struct coder
{
	int			index; //coder index, helps organize them into a circle
	long		last_compile_timestamp; //helps with output AND with time to burnout
	int			total_compiles; //individual coder compile number
	t_input		*limits; //passes data from input struct
}				t_coder;

t_input		*input_parse(char **in);
void		*start_thread(void *arg);
