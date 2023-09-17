#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

void task1() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

       // Bind the socket to an address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // You can use any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a client connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    printf("Received message from client: %s\n", buffer);

    // Send a response to the client
    const char *response = "Have a good day";
    int bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1)
    {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    close(clientSocket);
    close(serverSocket);
}

void task2() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

  // Bind the socket to an address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // You can use any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a client connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    printf("Received message from client: %s\n", buffer);

    // Send a response to the client
    int ct = 0;
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u')
        {
            ct++;
        }
    }
    char response[1024];
    snprintf(response, sizeof(response), "Number of vowels in the message is: %d", ct);
    int bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1)
    {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    close(clientSocket);
    close(serverSocket);
}

bool isPalindrome(const char* str) {
     int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
        {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

void task3() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

       // Bind the socket to an address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // You can use any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a client connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive data from the client
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    buffer[bytesRead] = '\0';
    printf("Received string from client: %s\n", buffer);

    // Check if the received string is a palindrome
    bool isPal = isPalindrome(buffer);

    // Send the result back to the client
    const char *response = isPal ? "String is palindrome" : "String is not palindrome";
    int bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1)
    {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }
    close(clientSocket);
    close(serverSocket);
}

void task4() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

      // Bind the socket to an address and port
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // You can use any available port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    // Accept a client connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1)
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive the integer array from the client
    int arr[100]; // Assuming a maximum array size of 100
    int numElements;

    int bytesRead = recv(clientSocket, &numElements, sizeof(numElements), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    bytesRead = recv(clientSocket, arr, numElements * sizeof(int), 0);
    if (bytesRead == -1)
    {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    printf("Received array from client: ");
    for (int i = 0; i < numElements; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Calculate the sum of array elements
    int sum = 0;
    for (int i = 0; i < numElements; i++)
    {
        sum += arr[i];
    }

    // Send the sum back to the client
    int bytesSent = send(clientSocket, &sum, sizeof(sum), 0);
    if (bytesSent == -1)
    {
        perror("Error sending data");
        exit(EXIT_FAILURE);
    }

    close(clientSocket);
    close(serverSocket);
}

int main() {
    // Uncomment the appropriate task function to run the desired task
    // task1();
    // task2();
    // task3();
    task4();

    return 0;
}
