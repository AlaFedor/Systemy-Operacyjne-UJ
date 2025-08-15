#include "biblioteka.h"
sem_t *semaphore;

void cleanup(){
	if(zamknij(semaphore) == 0){
        printf("blad zamykania semafora plik %s, linia %d", __FILE__, __LINE__);
	exit(8);
	}
	if(usun("/semafor") == 0){
        printf("blad usuwania semafora plik %s, linia %d", __FILE__, __LINE__);
	exit(9);
}

}


int main(int argc, char **argv){
if(argc != 4){
printf("podaj program do wywolania, liczbe procesow i liczbe sekcji krytycznych dla jednego procesu");
}
int sval;
int l_procesow = atoi(argv[2]);
int l_krytycznych = atoi(argv[3]);

atexit(cleanup);

 FILE *plik = fopen("numer.txt", "w");
    fprintf(plik, "%d", 0);
    fclose(plik);

 semaphore = stworz("/semafor", 1);
if (semaphore == SEM_FAILED) {
        printf("blad tworzenia semafora plik %s, linia %d", __FILE__, __LINE__);
        exit(1);
    }

if (signal(SIGINT, cleanup) == SIG_ERR){
	perror("Funkcja signal ma problem z SIGINT");
	exit(EXIT_FAILURE);
	}


for(int i=0; i<3; i++){
switch(fork()){
case -1:

	perror("fork error");
	exit(EXIT_FAILURE);

case 0:
	execlp(argv[1], argv[1], argv[3], NULL);
	perror("execlp error");
	_exit(5);

default:
	break;
}
}

	for(int i = 0; i<3; i++){
	wait(0);}

	plik = fopen("numer.txt", "r");
   	int numer;
   	fscanf(plik, "%d", &numer);
	fclose(plik);
	int lacznie = l_procesow * l_krytycznych;

	if(lacznie == numer){
	printf("numer w pliku jest poprawny\n");
	}
	else{
	printf("numer w pliku nie jest poprawny\n");
	}




return 0;
}
