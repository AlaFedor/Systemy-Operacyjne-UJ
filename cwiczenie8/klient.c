#include "biblioteka.h"

mqd_t server_queue, client_queue;
char client_queue_name[64];

void cleanup() {
    zamknij(server_queue);
    zamknij(client_queue);
    usun(client_queue_name);
    printf("Client cleanup completed.\n");
}

void handle_sigint(int sig) {
    exit(0);
}

int main() {
    pid_t pid = getpid();
    snprintf(client_queue_name, 64, "/%d", pid);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;



    client_queue = stworz(client_queue_name, &attr);
    server_queue = otworz(SERVER_QUEUE_NAME, O_WRONLY);

    atexit(cleanup);
    signal(SIGINT, handle_sigint);

    char input[MAX_SIZE];
    struct message msg;
    msg.client_pid = pid;

    while (1) {
        printf("wprowadz operacje (Ctrl+D by zakonczyc): ");
        if (fgets(input, MAX_SIZE, stdin) == NULL) {
            break;
        }

        snprintf(msg.text, MAX_SIZE, "%s", input);
        assert(wyslij(server_queue, &msg));

        assert(odbierz(client_queue, &msg));
        printf("Result: %s\n", msg.text);
    }

    return 0;
}
