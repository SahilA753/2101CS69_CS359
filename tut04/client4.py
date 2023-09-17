import socket
import struct

SERVER_HOST = "127.0.0.1"  # Server IP address (localhost)
SERVER_PORT = 12345       # Server port

def send_receive_data(data_to_send):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            client_socket.connect((SERVER_HOST, SERVER_PORT))
            client_socket.send(data_to_send)

            received_data = client_socket.recv(4)
            sum_of_elements = struct.unpack('i', received_data)[0]

            print(f"Server response: Sum of elements is {sum_of_elements}")
    except ConnectionRefusedError:
        print("Connection to the server was refused.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

if __name__ == "__main__":
    try:
        n = int(input("Please input n: "))  # Get the value of n from the user
        print("Please input arr (space-separated integers): ")
        integer_array = list(map(int, input().split()))[:n]  # Get the integer array from the user

        data_to_send = struct.pack(f"{len(integer_array)}i", *integer_array)
        send_receive_data(data_to_send)
    except ValueError:
        print("Invalid input. Please enter valid integers.")
