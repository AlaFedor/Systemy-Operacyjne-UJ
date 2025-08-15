#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]) {
 if (argc != 3) {
        printf("Podaj numer sygnalu i opcje jego obslugi!\n");
        printf("aby wykonac operacje domyslna wpisz 1, aby zignorowac wpisz 2, aby przechwycic wpisz 3\n");
    }

    int pid;
int n = atoi(argv[2]);
int sig = atoi(argv[1]);
int pid_matki = getpid();


    switch (pid = fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
	    int pid1 = getpid();
	    int pgid1 = getpgid(pid1);
	    setpgid(pid1, 0);
	    int pgid2 = getpgid(pid1);

	    printf("pid1: %d id grupy1: %d pid matki: %d pgid2:%d\n",pid1, pgid1, pid_matki, pgid2);

            execlp("./nowy.x", "./nowy.x", argv[1], argv[2], NULL);
            perror("execlp error");
            exit(2);
            break;

        default:
            sleep(1);
            if (kill(pgid1, 0) == 0) {
		for(int i=0; i<3; i++){
                kill(-pid, sig);
		sleep(1);
		}
            } else {
                printf("Proces potomny nie istnieje.\n");
            }

            int status;
            if (wait(&status) == -1) {
                perror("wait");
                exit(3);
            } else {
                if (WIFSIGNALED(status)) {
                    int signal_number = WTERMSIG(status);
                    printf("Proces potomny zostal zakonczony przez sygnal, PID: %d, Sygnal: %d, Nazwa: %s\n", pid, signal_number, strsignal(signal_number));
                } else {
                    printf("Proces lider zakonczyl sie w inny sposob, pid: %d, status:%d\n", pid_matki, status);
                }
            }
            break;
    }

    return 0;
}
