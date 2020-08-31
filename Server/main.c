//
//  main.c
//  personal poster
//
//  Created by Eric on 16-2-17.
//  Copyright (c) 2016年 Bakantu Eric. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PROT 8096

int main(int argc, const char * argv[]) {
    char string_send[255] = "Success";
    char buf[256];
    int s_fd, c_fd;
    int s_len, c_len;
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    if ((s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Socket failed");
        return -1;
    }
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = PROT;
    s_len = sizeof(s_addr);
    if (bind(s_fd, (struct sockaddr *)&s_addr, s_len) == -1) { printf("Bind failed!"); return -1;}
    listen(s_fd, 10);
    int key;
    pid_t pid;
    
    printf("Input key: (<= 6)");
    scanf("%d",&key);
    while(1){
        c_len = sizeof(c_addr);
        c_fd = accept(s_fd, (struct sockaddr *)&c_addr, (socklen_t*__restrict)&c_len);
        printf("#+# %s Login\n",inet_ntoa(c_addr.sin_addr));
        pid=fork();
        if(pid==-1)
        {
            printf("Fork failed");
        }
        if (pid == 0){
            recv(c_fd, buf, 256, 0);
            buf[strlen(buf)+1] = '\0';
            printf("#!#Receive message: %s From %s\n",buf,inet_ntoa(c_addr.sin_addr));
            write(c_fd,buf,sizeof(buf));
            send(c_fd, string_send, sizeof(string_send), 0);
        }
        if(pid>0){
            close(c_fd);
        }
    }
    return 0;
}
