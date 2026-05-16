#include "../include/Server.hpp"

#include <iostream>

Server::Server(int p)
{
    port = p;
    serverSocket = -1;
}

bool Server::start()
{
    std::cout << "Server starting on port " << port << std::endl;

    return true;
}