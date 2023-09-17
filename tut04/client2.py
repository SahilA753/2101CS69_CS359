import socket

def main():
    try:
        # Create a socket object
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Server IP address and port
        host = "127.0.0.1"  # Server IP address (localhost)
        port = 12345       # Server port

        # Connect to the server
        client_socket.connect((host, port))

        # Send a string to the server
        message = input("Enter a string: ")
        client_socket.send(message.encode())

        # Receive the count of vowels from the server
        vowel_count = client_socket.recv(1024).decode()
        print(f"Server response: The number of vowels in the string is {vowel_count}")

    except ConnectionRefusedError:
        print("Connection to the server was refused.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
