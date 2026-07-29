/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:22:00 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/07/29 14:51:00 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

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

typedef struct dongle
{
	int				index; //dongle's index equivalent to the coder index
	int				is_available; //checks if the dongle can be picked up
	int				is_ready; //checks if the dongle is ready for pickup
	int				cooldown_timestamp;
	pthread_mutex_t	mutex; //dongle lock
}					t_dongle;

typedef struct coder
{
	int				index; //coder index, helps organize them into a circle
	long			last_compile_timestamp; //helps time burnout
	int				total_compiles; //individual coder compile number
	t_input			*limits; //passes data from input struct
	t_dongle		*l_dong; //left dongle
	t_dongle		*r_dong; //right dongle
	pthread_mutex_t	mutex; //mutex for monitor perhaps
}					t_coder;

typedef struct monitor
{
	pthread_mutex_t	mutex;
	int couter;
} 	t_monitor;

t_input		*input_parse(char **in);
void		*start_thread(void *arg);
t_coder		*coder_creation(t_input *input);