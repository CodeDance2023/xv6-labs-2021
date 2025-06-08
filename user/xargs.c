#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/fcntl.h"  // 添加头文件
int main(int argc, char* argv[]) {
    sleep(10); //find . b | xargs grep hello 防止find .b 太慢执行，buf里读取不到数据
    // 创建要拓展的的参数数组和拓展的参数个数
    char *xargv[MAXARG];
    int xagrc = 0;  //拓展的参数的个数
    //获取通过当前命令执行时获取的命令行参数
    for (int i = 1; i < argc; i++) {    //xargs grep hello
        xargv[xagrc++] = argv[i];       //       0     1   xargv[0]:grep, xargv[1]: hello
    }
    //获取上一个命令通过管道进行io重定向输出的参数 例如："echo "1\n2" | xargs echo line" 
    char buf[MAXARG];                           // "1\n2"会重定向标准化输出到第二个命令的标准化输入
    read(0, buf, MAXARG);
    char *newArgs = buf; // 要获取的新参数字符串的首地址

    // 遍历buf，获取每一次命令新的命令行参数
    for (int i = 0; i < sizeof(buf); i++) {
        if (buf[i] == '\n') {
            buf[i] = 0;
            // 开启子线程去执行一次命令
            int pid = fork();
            if (pid > 0) {
                wait(0);
                newArgs = &buf[i + 1];
            }
            else {
                xargv[xagrc++] = newArgs;
                xargv[xagrc++] = 0;  //命令行参数结束标志
                exec(xargv[0], xargv);  //调用exec执行一次命令
                exit(0);
            }
        }
    }
    exit(0);
}