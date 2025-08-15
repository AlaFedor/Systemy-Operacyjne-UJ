#include "biblioteka.h"



sem_t *stworz(const char* name, int value) {
    sem_t* semaphore = sem_open(name, O_CREAT | O_EXCL, 0666, value);
    if (semaphore == SEM_FAILED) {
        perror("blad tworzenia semafora");
        return NULL;
    }
    return semaphore;
}



sem_t* open_semaphore(const char* name) {
    sem_t* semaphore = sem_open(name, 0);
    if (semaphore == SEM_FAILED) {
        perror("open_semaphore");
        return NULL;
    }
    return semaphore;
}

int wartosc(sem_t* semaphore) {
    int value;
    if (sem_getvalue(semaphore, &value) == -1) {
        perror("get_semaphore_value");
        return 0;
    }
    return value;
}

int opusc(sem_t* semaphore) {
    if (sem_wait(semaphore) == -1) {
        perror("wait_semaphore");
        return 0;
    }
    return 1;
}

int podnies(sem_t* semaphore) {
    if (sem_post(semaphore) == -1) {
        perror("wait_semaphore");
        return 0;
    }
    return 1;
}

int zamknij(sem_t *semaphore){
    if (sem_close(semaphore) == -1) {
        perror("close_semaphore");
        return 0;
    }
	return 1;
}

int usun(const char *name) {
    
    if (sem_unlink(name) == -1) {
	perror("unlink_semaphore");
        return 0;

            }
    	return 1;
}

