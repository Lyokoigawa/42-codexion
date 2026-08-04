/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:22:00 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/08/04 14:25:44 by lyokoiga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

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
	pthread_t		thread;
}					t_coder;

typedef struct heap
{
	t_coder	**coders;
	int		size;
	int		capacity;
}	t_heap;

typedef struct monitor
{
	t_input			*input;
	int				total_compiles;
	t_coder			*coders;
	pthread_mutex_t	print_mutex;
	pthread_t		thread;
	t_heap			*heap;
	
} 	t_monitor;

t_input		*input_parse(char **in);
void		*start_thread(void *arg);
t_coder		*coder_creation(t_input *input);
void		codex_comp(t_coder coder);
void		codex_debug(t_coder coder);
void		codex_refac(t_coder coder);