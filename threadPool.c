//Yuval Sirotkin 209323385

#include <pthread.h>
#include <stdio.h>
#include "threadPool.h"
#include "stdlib.h"

void* mainFuncOfNewThread(void* tp);
void freeAll(ThreadPool* tp);
int coin = 0;
int coout = 0;

// create new thread pool with numOfThreads threads
ThreadPool* tpCreate(int numOfThreads) {
    // create the thread pool
    ThreadPool* tp = (ThreadPool*)malloc(sizeof(ThreadPool));                                    //free the tp
    if (pthread_cond_init(&tp->condition, NULL) != 0 ) {
        perror("initialize condition failed");
        free(tp);
        exit(0);
    }
    if (pthread_mutex_init(&tp->mutex, NULL) != 0 ) {
        perror("initialize mutex failed");
        free(tp);
        exit(0);
    }
    if (pthread_mutex_init(&tp->mutexForCond, NULL) != 0 ) {
        perror("initialize mutex failed");
        free(tp);
        exit(0);
    }
    // initialize the thread pool
    tp->maxNumOfTP = numOfThreads;
    tp->runExistTasks = 1;
    tp->insertNewTasks =1;
    tp->numOfTaskInRQ = 0;
    tp->readyQueue = osCreateQueue();

    int i;
    pthread_t* threadsList = (pthread_t*)malloc(sizeof(pthread_t*) * numOfThreads);       // free the threadList
    if (threadsList == NULL) {
        perror("malloc failed");
        free(tp);
        exit(0);
    }
    tp->threads = threadsList;
    for (i = 0; i < numOfThreads; i++) {
        // create new user thread that will run the "mainFuncOfNewThread" function
        if (pthread_create(&threadsList[i], NULL, &mainFuncOfNewThread, tp) !=0 ) {
            perror("thread creation failed");
            free(tp);
            free(threadsList);
            exit(0);
        }
    }
    return tp;
}


int tpInsertTask(ThreadPool* threadPool, void (*computeFunc) (void *), void* param) {
    // if the thread pool was not destroyed - insert the new task
    if (threadPool->insertNewTasks) {
        //create struct of data for node in ready queue
        FuncAndParam *data = (FuncAndParam *) malloc(sizeof(FuncAndParam));
        if (data == NULL) {
            perror("malloc failed");
            freeAll(threadPool);
            exit(0);
        }
        data->computeFunc = computeFunc;
        data->param = param;
        if (pthread_mutex_lock(&threadPool->mutex) != 0 ) {
            perror("mutex lock failed");
            freeAll(threadPool);
            exit(0);
        }
        // insert the new task to the RQ
        osEnqueue(threadPool->readyQueue, (void *) data);
        coin++;
        if (coin == 5) {
            printf("5 in\n");
        }
        printf("%d %p \n" , coin, data);
        if (pthread_mutex_unlock(&threadPool->mutex) != 0 ) {
            perror("mutex unlock failed");
            freeAll(threadPool);
            exit(0);
        }
        threadPool->numOfTaskInRQ++;
        if (pthread_cond_signal(&threadPool->condition) != 0 ) {
            perror("condition signal failed");
            freeAll(threadPool);
            exit(0);
        }
        return 0;
    } else {
        if (pthread_mutex_lock(&threadPool->mutex) != 0 ) {
            perror("mutex lock failed");
            freeAll(threadPool);
            exit(-1);
        }
        freeAll(threadPool);
        return -1;
    }
    //freeAll(threadPool);
}

// first function of all new threads
void* mainFuncOfNewThread(void* tp){
    ThreadPool* threadPool = (ThreadPool*) tp;
    while (threadPool->runExistTasks) {
        // if the tp destroyed && the queue is empty -stop and call the signal for
        if (!threadPool->insertNewTasks && osIsQueueEmpty(threadPool->readyQueue)) {
            break; // go to end of the function and kill himself
        }
        // if there is task already in the thread pool and this thread is not in wait- run the task
        if (threadPool->numOfTaskInRQ > 0 ) {
            pthread_mutex_lock(&threadPool->mutex);
            void *topTask = osDequeue(threadPool->readyQueue);
            threadPool->numOfTaskInRQ--;
            pthread_mutex_unlock(&threadPool->mutex);
            // run the function
            if (topTask != NULL) {
                FuncAndParam *data = (FuncAndParam *) topTask;
                pthread_mutex_lock(&threadPool->mutex);
                coout++;
                printf("%d %p\n" , coout, data);
                pthread_mutex_unlock(&threadPool->mutex);
                data->computeFunc(data->param);
                free(data);

            }

        }
        else {   // makes the thread waiting until task was inserted to the readyQueue
            if (osIsQueueEmpty(threadPool->readyQueue)) {
                pthread_mutex_lock(&(threadPool->mutexForCond));
                printf("start waiting %lu\n", pthread_self());
                pthread_cond_wait(&(threadPool->condition), &(threadPool->mutexForCond));
                printf("stop waiting %lu\n", pthread_self());
                pthread_mutex_unlock(&(threadPool->mutexForCond));
            }
            // if the threadPool should still wait for new tasks- run the task from top of the readyQueue
            if (threadPool->runExistTasks && !osIsQueueEmpty(threadPool->readyQueue)) {
                pthread_mutex_lock(&threadPool->mutex);
                void *topTask = osDequeue(threadPool->readyQueue);
                threadPool->numOfTaskInRQ--;
                pthread_mutex_unlock(&threadPool->mutex);
                // run the function
                if (topTask != NULL) {
                    FuncAndParam *data = (FuncAndParam *) topTask;
                    data->computeFunc(data->param);
                    pthread_mutex_lock(&threadPool->mutex);
                    coout++;
                    printf("%d %p\n" , coout, data);
                    pthread_mutex_unlock(&threadPool->mutex);
                    free(data);

                    //free(topTask);
                }
            }
        }
    }
    //free(threadPool);
    //pthread_exit(NULL);
}


void tpDestroy(ThreadPool* threadPool, int shouldWaitForTasks) {
    printf("in destroy\n");
    if (!shouldWaitForTasks) {
        //pthread_cond_wait(&(threadPool->conditionForEnd), &(threadPool->mutexForEnd));
        threadPool->runExistTasks = 0;
        threadPool->insertNewTasks =0;
    } else {
        threadPool->insertNewTasks =0;
    }

    if (pthread_cond_broadcast(&threadPool->condition) != 0 ) {
        perror("Error in system call");
    }
    int i;
    for (i = 0; i < threadPool->maxNumOfTP; ++i) {
        // wait for all the threads to end running
        pthread_join(threadPool->threads[i], NULL);
    }
    pthread_mutex_lock(&threadPool->mutex);
    freeAll(threadPool);
    //endTheProcess
}

void freeRQ(ThreadPool* threadPool) {
    void *topTask = osDequeue(threadPool->readyQueue);
    while(topTask != NULL) {
        FuncAndParam *data = (FuncAndParam *) topTask;
        coout++;
        printf("des %d %p\n" , coout, data);
        free(data);
        topTask = osDequeue(threadPool->readyQueue);
    }
}

void freeAll(ThreadPool* tp) {
    if (tp != NULL) {
        if (tp->readyQueue != NULL) {
            freeRQ(tp);
            osDestroyQueue(tp->readyQueue);
        }
        if (tp->threads != NULL) {
            free(tp->threads);
        }
        pthread_mutex_unlock(&tp->mutex);
        free(tp);
    }
}
