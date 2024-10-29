#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPV4 AF_INET
#define TCP SOCK_STREAM
#define IP_ADDR "172.253.63.100" // sample IP 

int main()
{
    int SOCK = socket(IPV4, TCP, 0); // Create a TCP socket
    if (SOCK < 0)
    {
        perror("Socket creation failed");
        return 1; 
    }

    struct sockaddr_in SOCKET_ADDR;                         // Define a structure to hold socket address information
    SOCKET_ADDR.sin_family = IPV4;                          // Set address family to IPv4
    SOCKET_ADDR.sin_port = htons(80);                       // Set the port number for HTTP
    inet_pton(IPV4, IP_ADDR, &SOCKET_ADDR.sin_addr.s_addr); // Convert IP address from text to binary

    int res = connect(SOCK, (struct sockaddr *)&SOCKET_ADDR, sizeof(SOCKET_ADDR)); // Attempt to connect
    if (res < 0)
    {
        perror("Connection failed");
        return 1; 
    }
    puts("Connection was successful");

    char *msg = "GET / HTTP/1.1\r\nHost: google.com\r\nConnection: close\r\n\r\n";
    if (send(SOCK, msg, strlen(msg), 0) < 0)
    {
        perror("Send failed");
        return 1; 
    }

    char buffer[1024]; // Buffer to receive response
    int bytes_received = recv(SOCK, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0)
    {
        perror("Receive failed");
        return 1; 
    }

    buffer[bytes_received] = '\0'; // Null-terminate the buffer
    printf("YOUR RESULT IS:\n%s\n", buffer);

   
    return 0; 
}
