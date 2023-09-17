import socket
import struct

# Constants for server configuration
SERVER_HOST = '127.0.0.1'
SERVER_PORT = 12345

# Task 1: Echo Server
def task1():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((SERVER_HOST, SERVER_PORT))
    server_socket.listen(1)

    print("Task 1: Server listening on {}:{}".format(SERVER_HOST, SERVER_PORT))
    
    client_socket, client_address = server_socket.accept()
    print("Accepted connection from {}:{}".format(client_address[0], client_address[1]))
    message = client_socket.recv(1024).decode('utf-8')
    print("Received message from client: ", message)

    response = "Have a good day"
    client_socket.send(response.encode('utf-8'))
    client_socket.close()
    server_socket.close()

# Task 2: Count Vowels
def count_vowels(input_string):
    vowels = "AEIOUaeiou"
    vowel_count = sum(1 for char in input_string if char in vowels)
    return vowel_count

def task2():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((SERVER_HOST, SERVER_PORT))
    server_socket.listen()

    print("Task 2: Server is listening on {}:{}".format(SERVER_HOST, SERVER_PORT))

    client_socket, client_address = server_socket.accept()
    print("Connection established with {}:{}".format(client_address[0], client_address[1]))

    data = client_socket.recv(1024).decode()
    print("Received message from client: {}".format(data))

    vowel_count = count_vowels(data)

    client_socket.send(str(vowel_count).encode())

    client_socket.close()
    server_socket.close()

# Task 3: Check Palindrome
def is_palindrome(s):
    s = s.lower()
    return s == s[::-1]

def task3():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((SERVER_HOST, SERVER_PORT))
    server_socket.listen()

    print("Task 3: Server is listening on {}:{}".format(SERVER_HOST, SERVER_PORT))

    client_socket, client_address = server_socket.accept()
    print("Connection established with {}:{}".format(client_address[0], client_address[1]))

    data = client_socket.recv(1024).decode()
    print("Received message from client: {}".format(data))

    if is_palindrome(data):
        response_message = "String is palindrome"
    else:
        response_message = "String is not palindrome"

    client_socket.send(response_message.encode())

    client_socket.close()
    server_socket.close()

# Task 4: Sum of Integers in Array
def task4():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((SERVER_HOST, SERVER_PORT))
    server_socket.listen()

    print("Task 4: Server is listening on {}:{}".format(SERVER_HOST, SERVER_PORT))


    client_socket, client_address = server_socket.accept()
    print("Connection established with {}:{}".format(client_address[0], client_address[1]))

    data = client_socket.recv(1024)
    int_array = struct.unpack('!{}i'.format(len(data) // 4), data)
    array_sum = sum(int_array)

    client_socket.send(struct.pack('!i', array_sum))

    client_socket.close()
    server_socket.close()

def main():
    # Choose the task you want to execute (1, 2, 3, or 4)
    selected_task = 2

    if selected_task == 1:
        task1()
    elif selected_task == 2:
        task2()
    elif selected_task == 3:
        task3()
    elif selected_task == 4:
        task4()
    else:
        print("Invalid task number. Please choose a valid task.")

if __name__ == "__main__":
    main()
