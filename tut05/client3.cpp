#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int PORT = 8080;
const char* SERVER_IP = "127.0.0.1";

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Specify the server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Send a string to the server
    char message[100];
    printf("Enter the message to be sent to the server: ");
    scanf("%s", message);

    int bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    // Receive the server's response
    char response[1024];
    int bytesRead = recv(clientSocket, response, sizeof(response), 0);
    if (bytesRead == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    response[bytesRead] = '\0';
    printf("Server response: %s\n", response);

    close(clientSocket);

    return 0;
}
