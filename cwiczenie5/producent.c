//producent
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
char buf[1000];

	int potok = open("potok", O_WRONLY, 0644);
	if (potok == -1) {
           perror("blad otwierania potoku przez producenta");
           exit(EXIT_FAILURE);
    	}

	int plik = open("tekst", O_RDONLY, 0644);
	if (plik == -1) {
           perror("blad otwierania pliku przez producenta");
           exit(EXIT_FAILURE);
    	}

	size_t nbyte = sizeof(plik);


	while (read(plik, buf, nbyte) > 0){
		write(potok, buf, nbyte);
		printf("Producent: odczytuje i zapisuje do potoku: %s\n", buf);
		sleep(rand()%3);
	}
	close(potok);

	close(plik);
	unlink("potok");
	
	exit(1);

	
	return 0;
}
