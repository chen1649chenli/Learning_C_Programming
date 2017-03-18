#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>


#define MAX_SIZE 4096
#define QUEUE_NAME "/test queue"
#define STOP_MESSAGE "exit"


/*compilation command gcc mqueue_server.c -o mqueue_server -lrt*/

int main(int argc, char **argv){
    mqd_t mq;
    struct mq_attr attr;
    char buffer[MAX_SIZE + 1];
    /*define a flag to indicate when to quit message queue*/
    int must_stop = 0;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    //CHECK((mqd_t)-1 != mq);
    while(!must_stop){
      ssize_t bytes_read;

      /* receive the message */
      bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);

      buffer[bytes_read] = '\0';
      if (! strncmp(buffer, STOP_MESSAGE , strlen(STOP_MESSAGE))){
          must_stop = 1;
      } else {
          printf("Received: %s\n", buffer);
      }
    }
    return 0;
}
