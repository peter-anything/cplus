//
// Created by peter on 2020/2/18.
//

#ifndef CMAKEDEMO_THREADS_CPU_LIMIT_H
#define CMAKEDEMO_THREADS_CPU_LIMIT_H

#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <string>
#include "string_format.h"
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

const int NUM_THREADS = 5;

void *thread_main(void *threadid) {
    /* 把自己加入cgroup中（syscall(SYS_gettid)为得到线程的系统tid） */
    char cmd[128];
    sprintf(cmd, "echo %ld >> /sys/fs/cgroup/cpu/haoel/tasks", syscall(SYS_gettid));
    printf(cmd);
    system(cmd);
    sprintf(cmd, "echo %ld >> /sys/fs/cgroup/cpuset/haoel/tasks", syscall(SYS_gettid));
    printf(cmd);
    system(cmd);

    long tid;
    tid = (long) threadid;

    int a = 0;
    while (1) {
        a++;
    }
    pthread_exit(NULL);
}

void test(int argc, char *argv[])
{
    int num_threads;

    if (argc > 1)
    {
        num_threads = atoi(argv[1]);
    }

    if (num_threads <= 0 || num_threads >= 100){
        num_threads = NUM_THREADS;
    }

    mkdir("/sys/fs/cgroup/cpu/haoel", 755);
    system("echo 70000 > /sys/fs/cgroup/cpu/haoel/cpu.cfs_quota_us");

    mkdir("/sys/fs/cgroup/cpuset/haoel", 755);
    system("echo \"2,3\" > /sys/fs/cgroup/cpuset/haoel/cpuset.cpus");

    pthread_t * threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads);
    int rc;
    long t;
    for (t=0; t<num_threads; t++)
    {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, thread_main, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    free(threads);
}

#endif //CMAKEDEMO_THREADS_CPU_LIMIT_H
