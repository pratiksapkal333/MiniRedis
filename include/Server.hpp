#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
private:
    int serverSocket;
    int port;

    void handleCllient(int clientSocket);

public:
    Server(int p);

    bool start();
};

#endif