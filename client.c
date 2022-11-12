#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_IP   "127.0.0.1"
#define DEFAULT_PORT 6666

int main(int argc, char* argv[])
{
    char* SERVER_IP = DEFAULT_IP;
    int SERVER_PORT = DEFAULT_PORT;

    if (argc > 3) {
        printf("param err:\nUsage: %s ip port | %s port | %s\n", argv[0],
               argv[0], argv[0]);
    } else if (argc == 3) {
        SERVER_IP = argv[1];
        SERVER_PORT = atoi(argv[2]);
    } else if (argc == 2) {
        SERVER_PORT = atoi(argv[1]);
    } else {
        // Do nothing
    }

    int cliSocket;
    char* sendbuf = "Hello Server, I am Client.";

    if ((cliSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket err");
        exit(1);
    }

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port   = htons(SERVER_PORT);
    //    servAddr.sin_addr.s_addr = inet_addr(SERVER_IP);    //Outdated method
    inet_aton(SERVER_IP, &servAddr.sin_addr);

    if (connect(cliSocket, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        printf("connect err");
        exit(1);
    }

    printf("Connect with destination host %s:%d ...\n\n", SERVER_IP,
           SERVER_PORT);

    while (1) {
        int num = send(cliSocket, sendbuf, strlen(sendbuf) + 1, 0);
        if (num == (int)strlen(sendbuf) + 1) {
            printf("Send: Hello Server, I am Client.\nlength:%d\n\n", num);
        }
        else {
            printf("send err\n");
        }

        sleep(1);
    }

    close(cliSocket);
    return 0;
}
