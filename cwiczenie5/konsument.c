//konsument
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#define buf_size 100

int main(){

int wyjscie;
	char buf2[buf_size];
	wyjscie = open("nowy", O_WRONLY | O_TRUNC , 0644);
	if (wyjscie == -1) {
           perror("blad otwierania pliku przez konsumenta");
           exit(EXIT_FAILURE);
    	}

	int potok = open("potok", O_RDONLY, 0644);
	if (potok == -1) {
           perror("blad otwierania potoku przez konsumenta");
           exit(EXIT_FAILURE);
    	}

	

	while (read(potok, buf2, buf_size) > 0){
		write(wyjscie, buf2, buf_size);
		printf("Konsument: odczytuje i zapisuje do pliku: %s\n", buf2);
	sleep(rand()%3);
	}

	close(potok);
	close(wyjscie);
	unlink("potok");

	

	exit(2);

return 0;
}