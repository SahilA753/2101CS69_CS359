import socket

def main():
    try:
        # Create a socket object
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            # Server IP address and port
            host = "127.0.0.1"  # Server IP address (localhost)
            port = 12345       # Server port

            # Connect to the server
            client_socket.connect((host, port))

            # Send a string to the server
            message = input("Enter a string: ")
            client_socket.send(message.encode())

            # Receive the response from the server
            response = client_socket.recv(1024).decode()
            print(f"Server response: {response}")

    except ConnectionRefusedError:
        print("Connection to the server was refused.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

if __name__ == "__main__":
    main()