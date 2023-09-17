#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int BUFFER_SIZE = 1024;

int main() {
    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Server address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);                   // Server port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    // Connect to the server
    if (connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    char message[BUFFER_SIZE];
    printf("Enter the message to be sent to the server: ");
    scanf("%s", message);
    int messageLength = strlen(message);

    // Send the message
    int bytesSent = send(clientSocket, message, messageLength, 0);
    if (bytesSent == -1) {
        perror("Error sending data");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Receive a response from the server
    char buffer[BUFFER_SIZE];
    int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
    if (bytesRead == -1) {
        perror("Error receiving data");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data and print
    buffer[bytesRead] = '\0';
    printf("Received response from server: %s\n", buffer);

    // Close the socket
    close(clientSocket);

    return 0;
}
