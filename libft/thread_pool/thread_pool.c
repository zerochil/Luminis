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
		{
			pthread_mutex_unlock(&pool->queue_mutex);
			break ;
		}
		task = (t_task *)array_remove(&pool->task_queue, 0);
		if (task == NULL)
		{
			pthread_mutex_unlock(&pool->queue_mutex);
			continue ;
		}
		pthread_mutex_unlock(&pool->queue_mutex);
		pthread_cond_signal(&pool->queue_cond);
		task->func(task->arg);
	}
	return (NULL);
}

void	pool_init(t_thread_pool *pool)
{
	long	i;

	array_init(&pool->task_queue);
	pthread_mutex_init(&pool->queue_mutex, NULL);
	pthread_cond_init(&pool->queue_cond, NULL);
	pool->running = true;
	pool->num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	pool->workers = track_malloc(sizeof(t_thread_pool) * pool->num_threads);
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

	task = track_malloc(sizeof(t_task));
	task->func = func;
	task->arg = arg;
	pthread_mutex_lock(&pool->queue_mutex);
	array_push(&pool->task_queue, task);
	pthread_cond_signal(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
}

void	pool_wait(t_thread_pool *pool)
{
	pthread_mutex_lock(&pool->queue_mutex);
	while (pool->task_queue.size > 0)
		pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
	pthread_mutex_unlock(&pool->queue_mutex);
}

void	pool_destroy(t_thread_pool *pool)
{
	long	i;

	pthread_mutex_lock(&pool->queue_mutex);
	pool->running = false;
	pthread_cond_broadcast(&pool->queue_cond);
	pthread_mutex_unlock(&pool->queue_mutex);
	i = 0;
	while (i < pool->num_threads)
	{
		pthread_join(pool->workers[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&pool->queue_mutex);
	pthread_cond_destroy(&pool->queue_cond);
}
