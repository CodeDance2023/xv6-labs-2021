#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include <stddef.h>

//fork测试
int main() {
    int pid = fork();
    if (pid == 0) {
        printf("child: %d\n", pid );
        exit(0);
    }
    else {
       int status = -11111;
       int *p = &status;
        printf("status: %d\n", *p);
        printf("parent: %d\n",pid);
        exit(0);
    }
}