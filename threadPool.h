#ifndef __THREAD_POOL__
#define __THREAD_POOL__

#include <signal.h>
#include "osqueue.h"

typedef struct thread_pool
{
    int runExistTasks; // 1 if the tp is exist, 0 is the function "tpDestroy" was called with non zero
    int insertNewTasks; // 1 if the tp is exist, 0 is the function "tpDestroy" was called
    int numOfTaskInRQ;
    int maxNumOfTP;
    OSQueue* readyQueue;
    pthread_t* threads;
    pthread_cond_t condition;
    pthread_mutex_t mutex;
    pthread_mutex_t mutexForCond;

}ThreadPool;

typedef struct func_and_param
{
    void (*computeFunc) (void *);
    void* param;

}FuncAndParam;


ThreadPool* tpCreate(int numOfThreads);

void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks);

int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param);

#endif
