#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <csignal>


// Question 7
// int wait_till_pid(pid_t pid, int sec){
//     while (true) {
//         pid_t p = wait(nullptr);
//         if (p==-1 || p == pid) {
//             return p;
//         }
//     }
// }



