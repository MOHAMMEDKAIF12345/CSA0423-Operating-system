#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 1024

struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
} message;

int main() {
    key_t key;
    int msg_id;
    
    
    key = ftok("msg_queue", 65);
    
    
    msg_id = msgget(key, 0666 | IPC_CREAT);
    
   
    printf("Enter message to send: ");
    fgets(message.msg_text, MSG_SIZE, stdin);
    
    
    message.msg_type = 1;
    
    
    msgsnd(msg_id, &message, sizeof(message), 0);
    printf("Message sent: %s", message.msg_text);
    
    
    msgrcv(msg_id, &message, sizeof(message), 1, 0);
    printf("Message received: %s", message.msg_text);
    
   
    msgctl(msg_id, IPC_RMID, NULL);
    
    return 0;
}
