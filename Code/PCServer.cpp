#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


int main(int argc, char const *argv[])
{
    // Create a server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;

    // Set up the server's address information
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket to the specified address and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    // Start listening for incoming connections
    listen(server_socket, 5);

    std::cout << "Server is listening on port: 8080" << std::endl;

    // Message to be sent to the client
    char buffer[1024] = "Choose Command to be Processed: \n 01- Open Firefox \n 02- Open Terminal \n 03- Open Nautilus";

    // Accept a client connection
    int client = accept(server_socket, NULL, NULL);

    // Number of bytes read from the client
    int bytes = 1;

    // Send the buffer message to the client
    send(client, buffer, sizeof(buffer), 0);

    // Loop to receive and process commands from the client
    while (bytes)
    {
        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Read data from the client into the buffer
        bytes = read(client, buffer, sizeof(buffer));

        // Print the received data
        std::cout << "Received: " << buffer << std::endl;

        // Fork a new process
        pid_t pid = fork();
        if ((strcmp(buffer, "terminal\n") == 0))
        {
            // Execute code for opening terminal
            if (pid == 0)
            {
                execlp("gnome-terminal", "gnome-terminal", NULL);
                exit(0);
            }
        }
        else if ((strcmp(buffer, "browser\n") == 0))
        {
            // Execute code for opening browser
            if (pid == 0)
            {
                execlp("firefox", "firefox", NULL);
                exit(0);
            }
        }
        else if ((strcmp(buffer, "nautilus\n") == 0))
        {
            // Execute code for opening nautilus
            if (pid == 0)
            {
                execlp("nautilus", "nautilus", NULL);
                exit(0);
            }
        }
        else
        {
            // Execute code for wrong command
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, "Wrong Command");
            std::cout << "Wrong command" << std::endl;
            send(client, buffer, sizeof(buffer), 0);
        }
    }

    // Check if the client disconnected or an error occurred
    if (bytes == 0)
    {
        std::cout << "Client Disconnected" << std::endl;
    }
    else
    {
        std::cout << "Error!!" << std::endl;
    }

    // Close the server and client sockets
    close(server_socket);
    close(client);

    return 0;
}
