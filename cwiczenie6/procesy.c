#include "biblioteka.h"


int main(int argc, char **argv){

if(argc != 2){
	printf("podaj ilosc sekcji krytycznych dla procesu");
}
	sem_t *semaphore = open_semaphore("/semafor");
	int sval;
	int l_krytycznych = atoi(argv[1]);
	for(int i=0; i<l_krytycznych; i++){
	sval = wartosc(semaphore);
	printf("proces potomny jest przed sekcja krytyczna, wartosc semafora: %d\n", sval);
	assert(opusc(semaphore));
	sval = wartosc(semaphore);
	printf("proces potomny jest w sekcji krytycznej, wartosc semafora: %d\n", sval);
	 FILE *plik = fopen("numer.txt", "r+");
   	 int numer;
   	 fscanf(plik, "%d", &numer);
  	 numer++;
   	 srand(time(NULL));
    	 sleep(rand() % 3);
	 fseek(plik, 0, SEEK_SET); 
 	 fprintf(plik, "%d", numer);
   	 fclose(plik);
	assert(podnies(semaphore));
	sval = wartosc(semaphore);
	printf("proces potomny wyszedl z sekcji krytycznej, wartosc semafora: %d\n", sval);
	}
	if(zamknij(semaphore) == 0){
        printf("blad zamykania semafora plik %s, linia %d", __FILE__, __LINE__);
	_exit(7);
	}

	

return 0;
}
