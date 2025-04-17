/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:30:28 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/17 11:31:05 by rrochd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include "../containers/containers.h"
# include "../memory_management/memory_management.h"
# include <pthread.h>
# include <stdatomic.h>
# include <unistd.h>

typedef struct s_thread_pool
{
	pthread_t		*workers;
	t_array			task_queue;
	pthread_mutex_t	queue_mutex;
	pthread_mutex_t	wait_mutex;
	pthread_cond_t	queue_cond;
	pthread_cond_t	wait_cond;
	bool			running;
	long			num_threads;
	char			_pad1[64];
	atomic_int		pending_tasks;
	char			_pad2[64];
}					t_thread_pool;

typedef struct s_task
{
	void			(*func)(void *);
	void			*arg;
}					t_task;

void				pool_init(t_thread_pool *pool);
void				pool_add_task(t_thread_pool *pool, void (*func)(void *),
						void *arg);
void				pool_wait(t_thread_pool *pool);
void				pool_destroy(t_thread_pool *pool);

#endif
