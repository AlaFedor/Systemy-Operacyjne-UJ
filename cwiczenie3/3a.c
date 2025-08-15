
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


void my_sighandler(int sig){
    printf("sygnal zostanie przechwycony a proces zakonczony.\n");
    kill(getpid(), SIGKILL);
}

int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("Podaj numer sygnalu i opcje jego obslugi!\n");
        printf("aby wykonac operacje domyslna wpisz 1, aby zignorowac wpisz 2, aby przechwycic wpisz 3\n");
        exit(1);
    }

    int sig = atoi(argv[1]);
    int n = atoi(argv[2]);
    int x = getpid();

    printf("pid:%d\n", x);
    printf("n: %d\n", n);
    printf("sig: %d\n", sig);

    switch (n){
        case 1:
            if (signal(sig,SIG_DFL) == SIG_ERR){
                perror("Funkcja signal ma problem z sygnalem");
                exit(EXIT_FAILURE);
            } else{
                printf("Obsluga domyslna.\n");
                pause();
            }
            break;
        case 2:
            if (signal(sig,SIG_IGN) == SIG_ERR){
                perror("Funkcja signal ma problem z sygnalem");
                exit(EXIT_FAILURE);
            } else {
                printf("Sygna³ zostanie zignorowany.\n");
                pause();
            }
            break;
        case 3:
            if (signal(sig,my_sighandler) == SIG_ERR){
                perror("Funkcja signal ma problem z sygnalem");
                exit(EXIT_FAILURE);
		
            }
            else {
		pause();
                my_sighandler(sig);
     
            }
            break;
        default:
            printf("Niepoprawny rodzaj operacji");
            exit(EXIT_FAILURE);
    }

    return 0;
}
