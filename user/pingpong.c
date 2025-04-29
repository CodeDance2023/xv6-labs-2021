#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    int p[2];
    pipe(p);
    char buff[64];

    printf("!!\n");
    int pid = fork();
    if (pid < 0) {
        printf("error: fork failed!");
        exit(1);
    }

    else if (pid == 0) {
        read(p[0],buff,sizeof(buff));
        printf("收到来自父进程的信息：%s\n",buff);
        close(p[0]);
        int child_pid = getpid();
        printf("%d: received ping\n",child_pid);
        write(p[1],buff,sizeof(buff));
        close(p[1]);
        exit(0);
    }
    else
    {
        write(p[1],"a",1);
        close(p[1]);
        wait((int*)0);
        int parent_pid = getpid();
        read(p[0],buff,sizeof(buff));
        printf("收到来自子进程的信息: %s\n",buff);
        printf("%d: received pong\n",parent_pid);
        exit(0);
    }
}