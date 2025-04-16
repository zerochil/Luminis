#ifndef LIBTHREADS_H
#define LIBTHREADS_H

#include <pthread.h>
#include <unistd.h>
# include "../memory_management/memory_management.h"
# include "../containers/containers.h"


typedef struct {
    pthread_t       *workers;
    t_array         task_queue;
    pthread_mutex_t queue_mutex;
    pthread_cond_t  queue_cond;
    bool            running;
	long          num_threads;
} t_thread_pool;

typedef struct {
    void    (*func)(void*);
    void    *arg;
} t_task;

void	pool_init(t_thread_pool *pool);
void	pool_add_task(t_thread_pool *pool, void (*func)(void *), void *arg);
void	pool_wait(t_thread_pool *pool);
void	pool_destroy(t_thread_pool *pool);

#endif
