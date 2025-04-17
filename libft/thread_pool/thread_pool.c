/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrochd <rrochd@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:30:12 by rrochd            #+#    #+#             */
/*   Updated: 2025/04/17 20:33:12 by inajah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"

static void	*worker_thread(void *arg)
{
	t_thread_pool	*pool;
	t_task			*task;

	pool = (t_thread_pool *)arg;
	while (true)
	{
		pthread_mutex_lock(&pool->queue_mutex);
		while (pool->task_queue.size == 0 && pool->running)
			pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
		if (!pool->running)
			return (pthread_mutex_unlock(&pool->queue_mutex), NULL);
		task = (t_task *)array_remove(&pool->task_queue, 0);
		pthread_mutex_unlock(&pool->queue_mutex);
		if (task == NULL)
			continue ;
		task->func(task->arg);
		free(task);
		if (atomic_fetch_sub(&pool->pending_tasks, 1) == 1)
		{
			pthread_mutex_lock(&pool->wait_mutex);
			pthread_cond_broadcast(&pool->wait_cond);
			pthread_mutex_unlock(&pool->wait_mutex);
		}
	}
	return (NULL);
}

void	pool_init(t_thread_pool *pool)
{
	long	i;

	array_init(&pool->task_queue);
	pthread_mutex_init(&pool->queue_mutex, NULL);
	pthread_mutex_init(&pool->wait_mutex, NULL);
	pthread_cond_init(&pool->queue_cond, NULL);
	pthread_cond_init(&pool->wait_cond, NULL);
	pool->running = true;
	pool->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (pool->num_threads < 1)
		pool->num_threads = 4;
	pool->workers = track_malloc(sizeof(pthread_t) * pool->num_threads);
	pool->pending_tasks = 0;
	i = 0;
	while (i < pool->num_threads)
	{
		pthread_create(&pool->workers[i], NULL, worker_thread, pool);
		i++;
	}
}

void	pool_add_task(t_thread_pool *pool, void (*func)(void *), void *arg)
{
	t_task	*task;

	if (!pool->running)
		return ;
	task = safe_malloc(sizeof(t_task));
	task->func = func;
	task->arg = arg;
	pthread_mutex_lock(&pool->queue_mutex);
	array_push(&pool->task_queue, task);
	atomic_fetch_add(&pool->pending_tasks, 1);
	pthread_cond_signal(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
}

void	pool_wait(t_thread_pool *pool)
{
	pthread_mutex_lock(&pool->wait_mutex);
	while (atomic_load(&pool->pending_tasks) > 0)
		pthread_cond_wait(&pool->wait_cond, &pool->wait_mutex);
	pthread_mutex_unlock(&pool->wait_mutex);
}

void	pool_destroy(t_thread_pool *pool)
{
	long	i;
	t_task	*task;

	pthread_mutex_lock(&pool->queue_mutex);
	pool->running = false;
	pthread_cond_broadcast(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
	i = 0;
	while (i < pool->num_threads)
		pthread_join(pool->workers[i++], NULL);
	while (pool->task_queue.size > 0)
	{
		task = (t_task *)array_remove(&pool->task_queue, 0);
		if (task != NULL)
			free(task);
	}
	atomic_store(&pool->pending_tasks, 0);
	array_destroy(&pool->task_queue);
	pthread_mutex_destroy(&pool->queue_mutex);
	pthread_mutex_destroy(&pool->wait_mutex);
	pthread_cond_destroy(&pool->wait_cond);
	pthread_cond_destroy(&pool->queue_cond);
}
