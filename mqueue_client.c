#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>

#define MAX_SIZE 4096
#define QUEUE_NAME "/test queue"
#define STOP_MESSAGE "exit"

/*compilation command gcc mqueue_client.c -o mqueue_client -lrt*/

int main(int argc, char **argv)
{
    mqd_t mq;
    char buffer[MAX_SIZE];

    /* open the message queue */
    mq = mq_open(QUEUE_NAME, O_WRONLY);

    printf("Send to server (enter \"exit\" to stop it):\n");

    do {
        printf("> ");
        fflush(stdout);

        memset(buffer, '\0', MAX_SIZE);
        fgets(buffer, MAX_SIZE, stdin);

        /* send the message */
        mq_send(mq, buffer, MAX_SIZE, 0);

    } while (strncmp(buffer, STOP_MESSAGE , strlen(STOP_MESSAGE )));


    return 0;
}
