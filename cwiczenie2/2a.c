#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv){

if (argc!=2) {
        printf("Podaj jeden program do wywolania!\n");
        return -1;
    }
else{
printf("Identyfikatory procesu macierzystego: UID: %d, GID: %d, PID: %d, PGID: %d, PPID: %d\n",
		 getuid(), getgid(), getpid(), getpgid(getpid()), getppid());




for(int i=0; i<3; i++){
switch (fork())
{
case -1:

perror("fork error");
exit(1);

case 0:
execlp(argv[1], argv[1], NULL);
perror("execlp error");
exit(2);
break;

default:

wait(0);
break;

};
}
}
return 0;

}
