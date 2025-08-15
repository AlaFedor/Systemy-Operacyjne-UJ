#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

 if (argc != 3) {
        printf("Podaj numer sygnalu i opcje jego obslugi!\n");
        printf("aby wykonac operacje domyslna wpisz 1, aby zignorowac wpisz 2, aby przechwycic wpisz 3\n");
    }

int n = atoi(argv[2]);
int sig = atoi(argv[1]);

    int pid;

    switch (pid = fork()) {
        case -1:
            perror("fork error");
            exit(1);

        case 0:
            execlp("./3a.x", "./3a.x", argv[1], argv[2], NULL);
            perror("execlp error");
            exit(2);
            

        default:
            sleep(1);
            if (kill(pid, 0) == 0) {
                kill(pid, sig);
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
                    printf("Proces potomny zakoñczyl siê w inny sposób.\n");
                }
            }
            break;
    }

    return 0;
}
