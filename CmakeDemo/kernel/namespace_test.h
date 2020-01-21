//
// Created by peter on 2020/1/21.
//

#ifndef CMAKEDEMO_NAMESPACE_TEST_H
#define CMAKEDEMO_NAMESPACE_TEST_H

#define _GNU_SOURCE

#include <sched.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STACK_SIZE (1024 * 1024)
static char container_stack[STACK_SIZE];

#define errExit(code, msg); { if(code == -1) { perror(msg); exit(-1); } }\

char* const container_args[] = {
    "/bin/bash",
    NULL
};

static int container_func(void *args)
{
    pid_t pid = getpid();
    printf("Container[%d] - inside the container!\n", pid);
    execv(container_args[0], container_args);
    printf("Container[%d] - oops!\n", pid);

    return 1;
}

#endif //CMAKEDEMO_NAMESPACE_TEST_H
