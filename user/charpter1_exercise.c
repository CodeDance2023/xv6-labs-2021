// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "user/user.h"
// #include <time.h>
// #include <stddef.h>
// #include <time.h>
// int main() {
//     //父进程写，子进程读
//     int ptc[2];
//     //子进程写，父进程读
//     int ctp[2]; 

//     pipe(ptc);
//     pipe(ctp);

//     //times of transmission
    

//     //create a child process
//     int pid = fork();

//     time_t start = time(NULL);
//     int cnt = 0;

//     while (1) {
//     time_t curTime = time(NULL);
//     if (curTime - start >= 1.0) {
//         break;
//     }
//     if (pid == 0) {
//         char buff[1];
//         //child
//         //read the byte from parent
//         read(ptc[0],buff,1);
//         write(ctp[1],buff,1);
//         cnt += 1;
//     }
//     else {
//         char buff[1];
//         //parent
//         //write a byte to child
//         write(ptc[1],"a",1);
//         //read a byte from child
//         read(ctp[0],buff,1);
//         //read the byte from parent
//         write(ptc[1],buff,1);
//     }
// }
//     close(ptc[0]);
//     close(ptc[1]);
//     close(ctp[0]);
//     close(ctp[1]);
//     printf("%d\n",cnt);
//     exit(0);
// }