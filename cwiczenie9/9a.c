#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define ILOSC_WATKOW 5
#define ILOSC_CYKLI 3

pthread_mutex_t mutex;
int globalny = 0;

void* funkcja(void* arg) {
    int numer_watku = *(int*)arg;
    int prywatny = 0;

    for (int i = 0; i < ILOSC_CYKLI; ++i) {
	gotoxy(0,numer_watku);
        printf(" %d: sekcja prywatna, cykl: %d\n", numer_watku, i);
	sleep(1);
        pthread_mutex_lock(&mutex);
	gotoxy(50, numer_watku); 
        printf(" %d: sekcja krytyczna, cykl: %d\n", numer_watku, i);
        prywatny = globalny;
        prywatny++;
        sleep(1);
        globalny = prywatny;
        pthread_mutex_unlock(&mutex);
	gotoxy(0,numer_watku);
        printf(" %d: sekcja prywatna, cykl: %d\n", numer_watku, i);

        
    }

}

void gotoxy(unsigned x, unsigned y)
{
  printf("\033[%d;%dH\033[2K", y+1, x+1);
}

int main() {
    pthread_t threads[ILOSC_WATKOW];
    int numery_watkow[ILOSC_WATKOW];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < ILOSC_WATKOW; ++i) {
        numery_watkow[i] = i;
        if (pthread_create(&threads[i], NULL, funkcja, &numery_watkow[i]) != 0) {
            printf("blad tworzenia watku %d: %s\n", i, strerror(errno));
        }
      pthread_join(threads[i], NULL);

    }

    pthread_mutex_destroy(&mutex);

    if(globalny = ILOSC_WATKOW*ILOSC_CYKLI){
        printf("wartosc licznika globalnego jest prawidlowa\n");
    }
    else{
	printf("wartosc licznika globalnego jest nieprawidlowa\n");
    }


    return 0;
}
