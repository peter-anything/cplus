#include "namespace_test.h"

int main(int args, char* argv[])
{
    pid_t pid = getpid();
    printf("Parent[%d] - create a container!\n", pid);
    pid_t child_pid = clone

}