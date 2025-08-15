#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h> 

int potok;

void funkcja(){
if(unlink("potok") == -1){
 perror("blad usuwania potoku");
 exit(EXIT_FAILURE);
}
}

int main(){
atexit(funkcja);
srand(time(0));
size_t nbyte = 0;

if(mkfifo("potok", 0644) == -1 ) { 
perror("Blad funkcji mkfifo\n");
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
            perror("Blad fork");
            exit(EXIT_FAILURE);

case 0:

	int wyjscie;
	char buf2[100];
	wyjscie = open("nowy", O_WRONLY | O_TRUNC , 0644);
	if (wyjscie == -1) {
           perror("blad otwierania pliku przez konsumenta");
           exit(EXIT_FAILURE);
    	}

	potok = open("potok", O_RDONLY, 0644);
	if (potok == -1) {
           perror("blad otwierania potoku przez konsumenta");
           exit(EXIT_FAILURE);
    	}

	

	while (read(potok, buf2, nbyte) > 0){
		write(wyjscie, buf2, nbyte);
		printf("Konsument: odczytuje i zapisuje do pliku: %s\n", buf2);
	sleep(rand()%3);
	}

	close(potok);
	close(wyjscie);

	

	_exit(2);


default:
	char buf[1000];

	potok = open("potok", O_WRONLY, 0644);
	if (potok == -1) {
           perror("blad otwierania potoku przez producenta");
           exit(EXIT_FAILURE);
    	}

	while (read(plik, buf, nbyte) > 0){
		write(potok, buf, nbyte);
		printf("Producent: odczytuje i zapisuje do potoku: %s\n", buf);
		sleep(rand()%3);
	}
	close(potok);
	wait(0);

	close(plik);
	break;

	
	
}

return 0;


}
