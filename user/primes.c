#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prim(int p[])
{
    int p2[2], n, m;
    pipe(p2);
    close(p[1]);
    if(read(p[0], &n, sizeof(int)) == 0) {
        close(p[0]);
        exit(0);
    }
    printf("prime %d\n", n);
    if(fork() > 0) {
        close(p2[0]);
        while(read(p[0], &m, sizeof(int))) {
            if(m % n != 0) write(p2[1], &m, sizeof(int));
        }
        close(p[0]);
        close(p2[1]);
        wait(0);
        exit(0);
    } else{
        prim(p2);
        close(p[0]);
    }
}

int main()
{
    int n = 2, i;
    int p1[2];
    pipe(p1);
    if(fork() > 0) {
        close(p1[0]);
        printf("prime %d\n", n);
        for(i = 2 ; i <= 35; i++) {
            if(i % n != 0) write(p1[1], &i, sizeof(int));
        }
        close(p1[1]);
        wait(0);
    } else{
          prim(p1);
    }
    exit(0);
}