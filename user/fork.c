// fork()在父进程中返回子进程的PID
// 在子进程中返回0

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int pid = fork();
if(pid > 0) {
    printf("parent: child=%d\n", pid);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
} else if(pid == 0) {
    printf("child: exiting\n");
    exit(0);
} else {
    printf("fork error!\n"); 
}