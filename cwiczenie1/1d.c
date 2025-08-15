#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

int main(){
	printf("Identyfikatory procesu macierzystego: UID: %d, GID: %d, PID: %d, PGID: %d, PPID: %d\n",
		 getuid(), getgid(), getpid(), getpgid(getpid()), getppid());


	for(int i=0; i<3; i++){
		switch (fork())
		{
			case -1:
				perror("fork error");
				exit(1);

			case 0:
				sleep(3);
				printf("Identyfikatory procesu potomnego: UID: %d, GID: %d, PID: %d, PGID: %d, PPID: %d\n",
					 getuid(), getgid(), getpid(), getpgid(getpid()), getppid());
				break;

			default:
				sleep(5);
				break;

		}
	}

	return 0;

}
