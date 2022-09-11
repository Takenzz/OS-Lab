#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int p1[2], p2[2];
    char ch1, ch2;
    char ch3 = 'a';
    pipe(p2);
    pipe(p1);
    if(fork() == 0) {
        close(p1[1]);
        close(p2[0]);
        if(read(p1[0], &ch1, sizeof(char))) {
            printf("%d: received ping\n", getpid());
            write(p2[1], &ch1, sizeof(char));
            close(p2[1]);
            exit(0);
        }
        exit(1);
    }else {
        close(p2[1]);
        close(p1[0]);
        write(p1[1], &ch3, sizeof(char));
        close(p1[1]);
        wait(0);
        if(read(p2[0], &ch2, sizeof(char))) {
            printf("%d: received pong\n", getpid());
            exit(0);
        } 
        exit(1);           
    }
}