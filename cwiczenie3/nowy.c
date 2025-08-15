#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]){

if (argc!=3) {
        printf("Podaj numer procesu i rodzaj obslugi!\n");
        return -1;
    }
else{
int sig = atoi(argv[1]);
int pid1;

for(int i=0; i<3; i++){
switch (pid1 = fork())
{
case -1:

perror("fork error");
exit(1);

case 0:
int pid = getpid();
int pgid = getpgid(pid);
printf("pid: %d pgid: %d\n", pid, pgid);
execlp("./3a.x", "./3a.x", argv[1], argv[2], NULL);
perror("execlp error");
exit(2);
break;

default:
 int status;
 if (signal(sig,SIG_IGN) == SIG_ERR){
                perror("Funkcja signal ma problem z sygnalem (nowy)");
                exit(EXIT_FAILURE);
            }

if (wait(&status) == -1) {
                perror("wait");
                exit(3);
            } else {
                if (WIFSIGNALED(status)) {
                    int signal_number = WTERMSIG(status);
                    printf("Proces potomny zostal zakonczony przez sygnal, PID: %d, Sygnal: %d, Nazwa: %s status: %d\n", pid1, signal_number, strsignal(signal_number), status);
                } else {
                    printf("Proces zakoñczyl siê w inny sposób.\n");
                }
            }

break;

};
}
}
return 0;

}
