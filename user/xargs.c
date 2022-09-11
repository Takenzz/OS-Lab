#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char buf[512];
    char *arg[MAXARG];

    if(argc < 2) {
        printf("error : less parameter");
        exit(0);
    }
    for(int i = 1; i < argc; i++) {
        arg[i-1] = argv[i];
    }
    while(1) {
    char *a = buf;
    char b;
        while(read(0, &b, sizeof(char)) && b != '\n') {
            *a = b;
            a++;
        }
        *a = '\0';
        arg[argc - 1] = buf;
        if(fork() == 0) {
            exec(argv[1],arg);
            exit(0);
        } else{
            wait(0);
        }
        if(read(0, &b, sizeof(char)) == 0) break;
    }
    exit(0);
}