#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "osqueue.h"
#include "threadPool.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "osqueue.h"
#include "threadPool.h"

int j = 1;
pthread_mutex_t mutex;

void hello (void* a)
{
    printf("hello\n");
}

void toSleep (void* a)
{
    printf("in sleep\n");
    sleep(3);
    printf("after sleep\n");
}


void loop (void* a)
{
    pthread_mutex_lock(&mutex);
    printf("%d %lu\n", j, pthread_self());
    j++;
    pthread_mutex_unlock(&mutex);
}

void test_thread_pool_sanity()
{
    int i;

    ThreadPool* tp = tpCreate(5);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,hello,NULL);
    }
    //sleep(1);
    tpDestroy(tp,0);
    //tpInsertTask(tp,hello,NULL);
}

void loopTest()
{
    int i;

    ThreadPool* tp = tpCreate(5);
    for(i=0; i<300; ++i)
    {
        tpInsertTask(tp,loop,NULL);
    }
    usleep(1);
    tpDestroy(tp,0);
    //tpInsertTask(tp,hello,NULL);
}

void test_thread_pool_sanity_with_sleep()
{
    int i;

    ThreadPool* tp = tpCreate(5);
    tpInsertTask(tp,toSleep,NULL);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,hello,NULL);
    }
    //sleep(1);
    tpDestroy(tp,1);
    //tpInsertTask(tp,hello,NULL);
}

// should do all the sleep and then exit
void testShouldWait()
{
    int i;
    ThreadPool* tp = tpCreate(3);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,toSleep,NULL);
    }
    tpDestroy(tp,1);
}

// should do 3 sleeps
void testShouldNotWaitWithSleepOf1()
{
    int i;
    ThreadPool* tp = tpCreate(3);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,toSleep,NULL);
    }
    sleep(1);
    tpDestroy(tp,0);
}

// should do 5 sleeps
void testShouldNotWaitWithSleepOf4()
{
    int i;
    ThreadPool* tp = tpCreate(3);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,toSleep,NULL);
    }
    sleep(4);
    tpDestroy(tp,0);
}

// should do 5 sleeps
void testShouldNotWait()
{
    int i;
    ThreadPool* tp = tpCreate(3);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,toSleep,NULL);
    }
    tpDestroy(tp,0);
}


void testThreadWillWaitForTasks()
{
    int i;
    ThreadPool* tp = tpCreate(3);
    sleep(3);
    for(i=0; i<5; ++i)
    {
        tpInsertTask(tp,toSleep,NULL);
    }
    sleep(4);
    tpDestroy(tp,1);
}

void testTwoThreads()
{
    int i;
    ThreadPool* tp = tpCreate(2);
    sleep(3);
    for(i=0; i<10; ++i)
    {
        if (i % 2 == 1){

            tpInsertTask(tp,toSleep,NULL);
        } else {
            tpInsertTask(tp, hello, NULL);
        }
    }
    sleep(10);
    tpInsertTask(tp, hello, NULL);
    tpInsertTask(tp, toSleep, NULL);
    sleep(4);
    tpDestroy(tp,1);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    printf("origin test\n");
    test_thread_pool_sanity();

    printf("origin test with sleep\n");
    test_thread_pool_sanity_with_sleep();

    printf("2 threads, 10 tasks, sleep for 4\n");
    testTwoThreads();

    // all 5 should run (all 5 in Q)
    printf("should wait test- 3 threads\n");
    testShouldWait();

    //just 3 should run: all 5 in Q but just 3 running
    printf("shouldnt wait test sleep of 1 - 3 threads\n");
    testShouldNotWaitWithSleepOf1();

    // all 5 should run - all 5 in Q. in the first 3 sec the 3 first tasks will run. in the nest second the 2 other
    // will start to run but the destroy will wait for them
    printf("shouldnt wait test sleep of 4- 3 threads\n");
    testShouldNotWaitWithSleepOf4();

    // nothing will run (maybe 1/2/3 will run) - all of the tasks in the Q but probably no one will run until
    // the destroy will run
    printf("shouldnt wait with no sleep- 3 threads\n");
    testShouldNotWait();

    printf("test- threas will wait for tasks\n");
    testThreadWillWaitForTasks();

    printf("test- loop\n");
    loopTest();


    return 0;
}






//  ----origin test---
//void hello (void* a)
//{
//   printf("hello\n");
//}
//
//
//void test_thread_pool_sanity()
//{
//   int i;
//
//   ThreadPool* tp = tpCreate(5);
//
//   for(i=0; i<5; ++i)
//   {
//      tpInsertTask(tp,hello,NULL);
//   }
//   //sleep(1);
//   tpDestroy(tp,1);
//}
//
//
//int main()
//{
//   test_thread_pool_sanity();
//
//   return 0;
//}
