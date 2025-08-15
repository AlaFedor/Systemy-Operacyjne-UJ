#ifndef _BIBLIOTEKA_H
#define _BIBLIOTEKA_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>


sem_t *stworz(const char* name, int value);

sem_t* open_semaphore(const char* name);

int wartosc(sem_t *semaphore);

int opusc(sem_t *semaphore);

int podnies(sem_t *semaphore);

int usun(const char *name);

int zamknij(sem_t *semaphore);



#endif