//Yuval Sirotkin 209323385

#include <pthread.h>
#include <stdio.h>
#include "threadPool.h"
#include "stdlib.h"

void* mainFuncOfNewThread(void* tp);
void freeAll(ThreadPool* tp);

// create new thread pool with numOfThreads threads
ThreadPool* tpCreate(int numOfThreads) {
    // create the thread pool
    ThreadPool* tp = (ThreadPool*)malloc(sizeof(ThreadPool));                                    //free the tp
    pthread_cond_init(&tp->condition, NULL);
    pthread_mutex_init(&tp->mutex, NULL);
    pthread_mutex_init(&tp->mutexForCond, NULL);
    // initialize the thread pool
    tp->maxNumOfTP = numOfThreads;
    tp->runExistTasks = 1;
    tp->insertNewTasks =1;
    tp->numOfTaskInRQ = 0;
    tp->readyQueue = osCreateQueue();

    int i;
    pthread_t* threadsList = (pthread_t*)malloc(sizeof(pthread_t*) * numOfThreads);       // free the threadList
    for (i = 0; i < numOfThreads; i++) {
        // create new user thread that will run the "mainFuncOfNewThread" function
        pthread_create(&threadsList[i], NULL, &mainFuncOfNewThread, tp);
    }
    tp->threads = threadsList;
    return tp;
}


int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param) {
    // if the thread pool was not destroyed - insert the new task
    if (threadPool->insertNewTasks) {
        //create struct of data for node in ready queue
        FuncAndParam *data = (FuncAndParam *) malloc(sizeof(FuncAndParam));
        data->computeFunc = computeFunc;
        data->param = param;
        pthread_mutex_lock(&threadPool->mutex);
        printf("locked 42\n");
        // insert the new task to the RQ
        osEnqueue(threadPool->readyQueue, (void *) data);
        pthread_mutex_unlock(&threadPool->mutex);
        threadPool->numOfTaskInRQ++;
        printf("insert task unlock 42\n");
        pthread_cond_signal(&threadPool->condition);
    } else {
        // destory already freed all
        return -1;
    }
    return 0;
}

// first function of all new threads
void* mainFuncOfNewThread(void* tp){
    ThreadPool* threadPool = (ThreadPool*) tp;
    while (threadPool->runExistTasks) {
        printf("in while\n");
        // if the tp destroyed && the queue is empty -stop and call the signal for
        if (!threadPool->insertNewTasks && osIsQueueEmpty(threadPool->readyQueue)) {
            printf("need to break\n");
            //pthread_mutex_unlock(&threadPool->mutex);
            break; // go to end of the function and kill himself
        }
        // if there is task already in the thread pool and this thread is not in wait- run the task
        if (threadPool->numOfTaskInRQ > 0 ) {
            printf("num of task in RQ is non zero \n");
            pthread_mutex_lock(&threadPool->mutex);
            printf("locked 71\n");
            void *topTask = osDequeue(threadPool->readyQueue);
            printf("deQ in 72 %lu\n", pthread_self());
            threadPool->numOfTaskInRQ--;
            pthread_mutex_unlock(&threadPool->mutex);
            printf("unlocked 71\n");
            // run the function
            if (topTask != NULL) {
                FuncAndParam *data = (FuncAndParam *) topTask;
                data->computeFunc(data->param);
                free(data);
            }

        }
         else {   // makes the thread waiting until task was inserted to the readyQueue
            if (osIsQueueEmpty(threadPool->readyQueue)) {
                printf("start waiting %lu\n", pthread_self());
                pthread_mutex_lock(&(threadPool->mutexForCond));
                pthread_cond_wait(&(threadPool->condition), &(threadPool->mutexForCond));
                pthread_mutex_unlock(&(threadPool->mutexForCond));
                printf("stop waiting %lu\n", pthread_self());
            }
            // if the threadPool should still wait for new tasks- run the task from top of the readyQueue
            if (threadPool->runExistTasks && !osIsQueueEmpty(threadPool->readyQueue)) {
                printf("after wait if wait\n");
                pthread_mutex_lock(&threadPool->mutex);
                printf("locked 95\n");
                void *topTask = osDequeue(threadPool->readyQueue);
                printf("deQ in 99 %lu\n", pthread_self());
                threadPool->numOfTaskInRQ--;
                pthread_mutex_unlock(&threadPool->mutex);
                printf("unlocked 95\n");
                // run the function
                if (topTask != NULL) {
                    FuncAndParam *data = (FuncAndParam *) topTask;
                    data->computeFunc(data->param);
                    free(data);
                }
            }
        }
        //printf("end of while - or not exist or Q empty\n");
        // ending of the function - the thread is free and continue waiting for more tasks
    }
    printf("out of while\n");
    //printf("in end\n");
    if (pthread_cancel(pthread_self()) != 0) {
        freeAll(tp);
        perror("Error in System call");
        exit(-1);
    }
}


void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks) {
    printf("in destroy - remove this line\n");
    if (!shouldWaitForTasks) {
        //pthread_cond_wait(&(threadPool->conditionForEnd), &(threadPool->mutexForEnd));
        threadPool->runExistTasks = 0;
        threadPool->insertNewTasks =0;
    } else {
        threadPool->insertNewTasks =0;
    }

    if (pthread_cond_broadcast(&threadPool->condition) != 0 ) {
        printf("broadcast failed\n");
        perror("Error in system call");
    }
    printf("after brodcast\n");
    for (int i = 0; i < threadPool->maxNumOfTP; ++i) {
        // wait for all the threads to end running
        pthread_join(threadPool->threads[i], NULL);
    }
    printf("after join\n");
    freeAll(threadPool);
    //endTheProcess
}


void freeAll(ThreadPool* tp) {
    if (tp != NULL) {
        if (tp->readyQueue != NULL) {
            osDestroyQueue(tp->readyQueue);
        }
        if (tp->threads != NULL) {
            free((tp->threads));
        }
        free(tp);
    }
}
