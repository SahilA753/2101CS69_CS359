#include <iostream>
#include <vector>
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
    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Send an integer array to the server
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;
    std::cout << std::endl;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cout << "Enter element " << i + 1 << ": ";
        std::cin >> arr[i];
        std::cout << std::endl;
    }

    int numElements = arr.size();

    int bytesSent = send(clientSocket, &numElements, sizeof(numElements), 0);
    if (bytesSent == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    bytesSent = send(clientSocket, arr.data(), numElements * sizeof(int), 0);
    if (bytesSent == -1) {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    // Receive the sum of array elements from the server
    int sum;
    int bytesRead = recv(clientSocket, &sum, sizeof(sum), 0);
    if (bytesRead == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    printf("Received sum from server: %d\n", sum);

    close(clientSocket);

    return 0;
}
