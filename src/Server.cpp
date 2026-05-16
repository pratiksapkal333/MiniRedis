#include "../include/Server.hpp"
#include <iostream>
#include <thread>
#include <cstring>

// Linux networking headers
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

Server::Server(int p)
{
    port = p;
    serverSocket = -1;
}

void Server::handleCllient(int clientSocket)
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer)); // Clears buffer before reuse.

        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0); // Reads bytes from socket.
        if (bytesReceived <= 0)
        {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        std::cout << "Client says: " << buffer << std::endl;
    }
    close(clientSocket);
}

bool Server::start()
{
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Checks if socket creation is failed
    if (serverSocket < 0)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    // Prevent bind errors on restart / allow port resuse
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    std::cout << "Socket created successfully" << std::endl;

    // Configure server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to port
    if (bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return false; // notify if bind failed
    }
    std::cout << "Bind Successful" << std::endl;

    // Start listening
    if (listen(serverSocket, 5) < 0)
    {
        std::cerr << "Listen Failed" << std::endl;
        return false; // notify if listen failed
    }
    std::cout << "Server listening on port" << port << std::endl;

    // Infinite server loop
    while (true)
    {
        sockaddr_in clientAddress;
        socklen_t clientSize = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (sockaddr *)&clientAddress, &clientSize);

        if (clientSocket < 0)
        {
            std::cerr << "Client accept failed" << std::endl;
            continue; // notify if accept failed
        }
        std::cout << "Client connected" << std::endl;

        // Create thread for client
        std::thread clientThread(&Server::handleCllient, this, clientSocket);
        clientThread.detach(); // Allows thread to run independently Server continues accepting new client
    }

    // close sockets
    close(serverSocket);
    return true;
}