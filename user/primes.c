#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/*
为什么关闭一个副本会影响递归调用？

文件描述符是进程独立的，但你的代码中：

递归调用时，fd 是同一个数组（地址相同）。

每次递归的 fork() 会继承 当前进程的文件描述符状态。

如果上一级递归关闭了 fd[0]，下一级递归继承的就是 已关闭的 fd[0]
*/

void fun(int* fd) {
    char buffer[36];
    read(fd[0], buffer, 36);
    printf("%s", buffer);
    close(fd[0]); // 关闭子进程的读端，子进程的子进程利用新管道newfd进行读取数据
    int index = 0;
    for (int i = 2; i <= 35; i++) {   //找到第一个最小的素数
        if (buffer[i] == '1') {
            index = i;
            break;
        }
    }
    if (index == 0) {   //说明素数已经筛完，不需要再继续创建进程
        exit(0);
    }

    printf("prime %d\n", index);
    buffer[index] = '0';   //将本次的素数设置为不是素数，防止子进程再次把它当作筛
    for (int j = index * index; j <= 35; j += index) {
        buffer[j] = '0';
    }
    close(fd[1]);    //子进程利用新管道写出数据给它的子进程，因此这个写端已经没用

    // 新建一个管道,防止各对父子进程的文件描述符相互影响
    int newfd[2];
    pipe(newfd);
    int pid = fork();
    if (pid > 0) {
        write(newfd[1], buffer, 36);
    }
    else {
        fun(newfd);
        wait(0);
        exit(0);
    }
}

int main() {
    int fd[2];
    pipe(fd);
    char isPrime[36];
    for (int i = 2; i <= 35; i++) {
        isPrime[i] = '1';
    }

    int pid = fork();
    if (pid > 0) {
        close(fd[0]);   //关闭没用的写端
        write(fd[1], isPrime, 36);
        wait(0);
        close(fd[1]);   //等待子进程结束后才关闭写端，防止父进程未写完，就关闭写端
    }
    else {
        fun(fd);
        wait(0);
    }
    exit(0);
}