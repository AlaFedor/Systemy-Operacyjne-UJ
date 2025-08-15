#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(){

    printf("Numer UID:%d\n", getuid());
    printf("Numer GID:%d\n", getgid());
    printf("Numer PID:%d\n", getpid());
    printf("Numer PPID:%d\n", getppid());
    printf("Numer PGID:%d\n", getpgid(getpid()));

    return 0;
}