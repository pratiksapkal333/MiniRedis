#include "../include/Server.hpp"

#include <iostream>

// Linux socket headers
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

Server::Server(int p)
{
    port = p;
    serverSocket = -1;
}

bool Server::start()
{
    // Create socket
    serverSocket = socket(AF_INET,
                          SOCK_STREAM,
                          0);

    if (serverSocket < 0)
    {
        std::cerr << "Socket creation failed"
                  << std::endl;

        return false;
    }

    std::cout << "Socket created successfully"
              << std::endl;

    // Configure server address
    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(serverSocket,
             (sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        std::cerr << "Bind failed"
                  << std::endl;

        return false;
    }

    std::cout << "Bind successful"
              << std::endl;

    // Listen for clients
    if (listen(serverSocket, 5) < 0)
    {
        std::cerr << "Listen failed"
                  << std::endl;

        return false;
    }

    std::cout << "Server listening on port "
              << port << std::endl;

    // Accept one client
    sockaddr_in clientAddress;
    socklen_t clientSize =
        sizeof(clientAddress);

    int clientSocket = accept(
        serverSocket,
        (sockaddr*)&clientAddress,
        &clientSize
    );

    if (clientSocket < 0)
    {
        std::cerr << "Client accept failed"
                  << std::endl;

        return false;
    }

    std::cout << "Client connected"
              << std::endl;

    close(clientSocket);
    close(serverSocket);

    return true;
}