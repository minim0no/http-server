#ifndef HTTP_TCPSERVER
#define HTTP_TCPSERVER
#include <sys/socket.h>
#include <sys/types.h>

class TcpServer {
    public:
        TcpServer();
        ~TcpServer();
    
    private:
        startServer();
        closeServer();
        int mSocket;
}

#endif