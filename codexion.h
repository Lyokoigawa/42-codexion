/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:22:00 by lyokoiga          #+#    #+#             */
/*   Updated: 2026/09/11 13:08:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct heap			t_heap;

typedef struct simulation	t_simulation;

typedef struct input
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
	int				is_ready; //checks if the dongle is ready for pickup
	int				in_use; //checks if the dongle is currently in use
	long			cooldown_start; //timestamp for cooldown start
	pthread_mutex_t	mutex; //dongle lock
	t_heap			*heap; //pointer to the heap for scheduling
}					t_dongle;

typedef struct coder
{
	int				index; //coder index, helps organize them into a circle
	long			last_compile_timestamp; //helps time burnout
	int				total_compiles; //individual coder compile number
	int				can_compile; //flag to check if coder can compile
	t_simulation	*sim; //passes data from input struct
	t_dongle		*l_dong; //left dongle
	t_dongle		*r_dong; //right dongle
	pthread_mutex_t	mutex; //mutex for monitor perhaps
	pthread_cond_t	cond; //condition variable for signaling
	pthread_t		thread;
}					t_coder;

typedef struct request
{
	t_coder	*coder;
	long	timestamp;
	long	deadline;
}			t_request;

typedef struct heap
{
	t_request	**request;
	int			size;
	int			capacity;
}				t_heap;

typedef struct scheduler
{
	t_request		**queue;
	int				queue_size;
	t_heap			*heap;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}					t_scheduler;

typedef struct simulation
{
	t_input				*input;
	t_coder				*coders;
	t_dongle			*dongles;
	t_scheduler			scheduler;
	int					running;
	int					start;
	long				start_time;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		state_mutex;
	pthread_cond_t		start_cond;
	pthread_t			monitor;
}						t_simulation;

t_input			*input_parse(char **in);
void			*start_thread(void *arg);
void			*sim_start(void *arg);
t_simulation	*simulation_creation(t_input *input);
t_coder			*coder_creation(t_simulation *sim);
t_dongle		*dongle_creation(t_input *input);
int				codex_comp(t_coder *coder);
int				codex_debug(t_coder *coder);
int				codex_refac(t_coder *coder);
void			check_burnout(t_coder *coder);
void			sim_run(t_simulation *sim);
int				simulation_running(t_simulation *sim);
void			print_status(t_coder *coder, const char *action);
void			update_last_compile(t_coder *coder);
void			init_heap(t_heap *heap, int capacity);
void			init_scheduler(t_simulation *sim, t_heap *heap);
void			heap_push(t_simulation *sim, t_request *request);
void			heap_pop(t_simulation *sim);
void			heapify_up(t_heap *heap, int index, int policy);
void			heapify_down(t_heap *heap, int index, int policy);
void			accept_request(t_simulation *sim, t_request *request);
int				is_higher(t_request *a, t_request *b, int policy);
int				higher_child(t_heap *heap, int left_index, int right_index,
					int policy);
void			coder_request(t_coder *coder);
t_request		*heap_peek(t_simulation *sim);
void			check_request(t_simulation *sim);
int				can_fulfill(t_request *request, t_simulation *sim);
void			consume_dongles(t_request *request);
void			restore_queue(t_simulation *sim);
void			queue_request(t_simulation *sim, t_request *to_queue);
int				dongle_available(t_dongle *dongle, t_simulation *sim);
void			lock_dongles(t_coder *coder);
void			unlock_dongles(t_coder *coder);
void			input_error(int i);
void			feasibility_error(int error);
void			destroy_simulation(t_simulation *sim);
void			individual_input_check(int *in);
void			individual_input_error(int error);
t_simulation	*spawn_world(t_input *in);
void			run_world(t_simulation *sim);
void			kill_world(t_simulation *sim);	

long			get_current_time(void);
int				ft_usleep(long miliseconds, t_simulation *monitor);
void			ft_sleep_ms(long ms);
long			elapsed_time(long start);
void			get_deadline(struct timespec *ts, long wait_ms);
void			coder_sleep(t_coder *coder, long time_to_wait);
