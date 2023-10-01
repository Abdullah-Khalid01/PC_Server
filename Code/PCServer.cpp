#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>


int main(int argc, char const *argv[])
{
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in server_address;

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(8080);
        server_address.sin_addr.s_addr = INADDR_ANY;

        
        bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

        listen(server_socket,5);

        std::cout << "Server is listening on port: 8080" << std::endl;

        char buffer[1024]= "Choose Command to be Processed: \n 01- Open Firefox \n 02- Open Terminal \n 03- Open Nautilus";

        int client = accept(server_socket,NULL,NULL);

        int bytes = 1;

        send(client, buffer, sizeof(buffer), 0);

    while(bytes)
    {
        memset(buffer,0,sizeof(buffer));

        bytes = read(client,buffer,sizeof(buffer));

        std::cout << "Recieved: " << buffer << std::endl;

        pid_t pid = fork();
        if((strcmp(buffer,"terminal\n")==0))
        {
            std::cout << "ter" << std::endl;
            if(pid == 0)
            {
                execlp("gnome-terminal" , "gnome-terminal" , NULL);
                exit(0);
            }
        }
        else if ((strcmp(buffer,"browser\n")==0))
        {
            std::cout << "fire" << std::endl;
            if(pid == 0)
            {
                execlp("firefox" , "firefox" , NULL);
                exit(0);
            }
        }
        else if ((strcmp(buffer,"nautilus\n")==0))
        {
            std::cout << "nauti" << std::endl;
            if(pid ==0)
            {
                execlp("nautilus" , "nautilus" , NULL);
                exit(0);
            }
        }
        else
        {
            memset(buffer,0,sizeof(buffer));
            strcpy(buffer,"Wrong Command");
            std::cout << "wrong" << std::endl;
            send(client, buffer, sizeof(buffer), 0);
        }
    }

    if (bytes == 0)
    {
        std::cout << "Client Disconnected" << std::endl;
    }
    else
    {
        std::cout << "Error!!" << std::endl;
    }
    
    close (server_socket);
    close(client);
    return 0;
}