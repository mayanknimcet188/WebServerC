#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    char ch = 'A';

    // create a socket for the client
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    // name the socket
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
    // connect the client socket to the server socket
    if (connect(sockfd, (struct sockaddr *)&address, len) == -1)
    {
        perror("oops: client1");
        exit(1);
    }
    // read and write via sockfd
    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}