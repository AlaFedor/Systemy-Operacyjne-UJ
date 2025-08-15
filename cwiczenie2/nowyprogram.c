#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
printf("Identyfikatory procesu potomnego: UID: %d, GID: %d, PID: %d, PGID: %d, PPID: %d\n",
		 getuid(), getgid(), getpid(), getpgid(getpid()), getppid());

return 0;
}
