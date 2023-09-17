import socket

SERVER_HOST = '127.0.0.1'  # Replace with the server's IP address
SERVER_PORT = 12345  # Replace with the server's port

def main():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            client_socket.connect((SERVER_HOST, SERVER_PORT))
            message = "Hello, IITP"
            client_socket.send(message.encode('utf-8'))

            response = client_socket.recv(1024).decode('utf-8')
            print("Received response from server:", response)
    except ConnectionRefusedError:
        print("Connection to the server refused.")
    except Exception as e:
        print("An error occurred:", str(e))

if __name__ == "__main__":
    main()
