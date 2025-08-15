#include "biblioteka.h"

mqd_t server_queue;


void cleanup() {
    zamknij(server_queue);
    usun(SERVER_QUEUE_NAME);
    printf("Server cleanup completed.\n");
}

void handle_sigint(int sig) {
    exit(0);
}


int main(){
 atexit(cleanup);
    signal(SIGINT, handle_sigint);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;


server_queue = stworz(SERVER_QUEUE_NAME, &attr);
printf("Czekam na wiadomosc...\n");


    while (1) {
        struct message msg;
        if (odbierz(server_queue, &msg) == -1) {
            printf("blad odbierania wiadomosci");
        }

        printf("Odebrano wiadomosc: %s od: %d\n", msg.text, msg.client_pid);

        char operator;
        int num1, num2, result;
        sscanf(msg.text, "%d%c%d", &num1, &operator, &num2);

        mqd_t client_queue;
        char client_queue_name[64];
        snprintf(client_queue_name, 64, "/%d", msg.client_pid);
        client_queue = otworz(client_queue_name, O_WRONLY);

        switch (operator) {
            case '+': result = num1 + num2;
			snprintf(msg.text, MAX_SIZE, "%d", result);
			 break;
            case '-': result = num1 - num2;
			snprintf(msg.text, MAX_SIZE, "%d", result);	
			 break;
            case '*': result = num1 * num2; 
				snprintf(msg.text, MAX_SIZE, "%d", result);
				break;
            case '/':
			if (num2 == 0) {
                          snprintf(msg.text, MAX_SIZE, "error: dzielenie przez 0");
                        }
                    result = num1 / num2;
		    snprintf(msg.text, MAX_SIZE, "%d", result);
 
                    break;
            default: 
                snprintf(msg.text, MAX_SIZE, "nieznana operacja");
			break;
        }

        assert(wyslij(client_queue, &msg));
        assert(zamknij(client_queue));
    }




return 0;
}