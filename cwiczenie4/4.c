#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main(){
int filedes[2];
size_t nbyte = 0;


if( pipe(filedes) == -1 ) { 
perror("Blad funkcji pipe\n");
exit(EXIT_FAILURE);
}

int plik;
plik = open("tekst", O_RDONLY, 0644);
	if (plik == -1) {
           perror("blad otwierania pliku przez producenta");
           exit(EXIT_FAILURE);
    	}
	nbyte = sizeof(plik);



switch(fork()){

case -1:
            perror("B³¹d fork");
            exit(EXIT_FAILURE);

case 0:
	close(filedes[1]);
	int wyjscie;
	char buf2[1000];
	wyjscie = open("nowy", O_WRONLY | O_TRUNC , 0644);
	if (wyjscie == -1) {
           perror("blad otwierania pliku przez konsumenta");
           exit(EXIT_FAILURE);
    	}
	

	while (read(filedes[0], buf2, nbyte) > 0){
		write(wyjscie, buf2, nbyte);
		printf("Konsument: odczytuje i zapisuje do pliku: %s\n", buf2);
	sleep(0);
	}

	close(filedes[0]);
	close(wyjscie);

	break;


default:
	close(filedes[0]);
	char buf[1000];

	while (read(plik, buf, nbyte) > 0){
		write(filedes[1], buf, nbyte);
		printf("Producent: odczytuje i zapisuje do potoku: %s\n", buf);
		sleep(1);
	}
	close(filedes[1]);
	wait(0);

	close(plik);
	break;

	
	
}

return 0;


}



