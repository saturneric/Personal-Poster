//
//  main.c
//  presonal poster client
//
//  Created by Eric on 16-2-17.
//  Copyright (c) 2016年 Bakantu Eric. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PROT 8884
#define N_MAX 256

int main(int argc, const char * argv[]) {
    int sockfd;
    int len;
    struct sockaddr_in addr;
    int newsockfd;
    char buf[N_MAX];
    int len2;
    char rebuf[N_MAX];
    int i,key;
    char ch;
    
    printf("Input key: (<= 6)");
    scanf("%d",&key);
    getchar();
    
    while (1){
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = PROT;
        len = sizeof(addr);
        newsockfd = connect(sockfd, (struct sockaddr *)&addr, len);
        if (newsockfd == -1){
            printf("Fail in connect the Server!");
            return -1;
        }
        
        printf("SEND: ");
        i = 0;
        while ((ch = getchar()) != '\n'){
            buf[i] = ch;
            i++;
        }
        buf[i] = '\0';
        if (!strcmp(buf, "quit")) break;
        for (i = 0; i < strlen(buf); i++){
            if (buf[i] == ' ') buf[i] = '_';
            buf[i] += key;
        }
        len2 = sizeof(buf);
        send(sockfd, buf, len2, 0);
        
        
        usleep(1000);
        recv(sockfd, rebuf, N_MAX, 0);
        rebuf[strlen(rebuf)+1] = '\0';
        printf("Receive message: %s\n",rebuf);
        close(sockfd);
    }
    return 0;
}
