#include "biblioteka.h"

mqd_t stworz(const char *name, struct mq_attr *attr){
  mqd_t queue = mq_open(name, O_CREAT | O_RDWR, 0644, attr);
    if (queue == (mqd_t) -1) {
        perror("Error creating queue");
        exit(EXIT_FAILURE);
    }
    return queue;
}

mqd_t otworz(const char *name, int oflag) {
    mqd_t queue = mq_open(name, oflag);
    if (queue == (mqd_t) -1) {
        perror("Error opening queue");
        exit(EXIT_FAILURE);
    }
    return queue;
}

int wyslij(mqd_t queue, struct message *msg)
 {
    if (mq_send(queue, (const char *) msg, sizeof(struct message), 0) == -1) {
        perror("Error sending message");
        return 0;
    }
    return 1;
}

int odbierz(mqd_t queue, struct message *msg){
    if (mq_receive(queue, (char *) msg, sizeof(struct message), NULL) == -1) {
        perror("Error receiving message");
        return 0;
    }
    return 1;
}


int zamknij(mqd_t queue){
    if (mq_close(queue) == -1) {
        perror("Error closing queue");
        return 0;
    }
    return 1;
}

int usun(const char *name) {
    if (mq_unlink(name) == -1) {
        perror("Error deleting queue");
        return 0;
    }
    return 1;
}


