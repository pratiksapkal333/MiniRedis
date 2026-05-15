#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
private:
    int serverSocket;
    int port;

public:
    Server(int p);

    bool start();
};

#endif