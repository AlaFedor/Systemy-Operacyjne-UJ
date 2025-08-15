#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>

#define MAX_SIZE 1024
#define SERVER_QUEUE_NAME "/server_queue"
#define MAX_SIZE 1024
#define MSG_BUFFER_SIZE (MAX_SIZE + 10)

struct message {
    pid_t client_pid;
    char text[MAX_SIZE];
};


mqd_t stworz(const char *name, struct mq_attr *attr);
mqd_t otworz(const char *name, int oflag);
int wyslij(mqd_t queue, struct message *msg);
int odbierz(mqd_t queue, struct message *msg);
int zamknij(mqd_t queue);
int usun(const char *name);




#endif