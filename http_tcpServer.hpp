#ifndef HTTP_TCPSERVER
#define HTTP_TCPSERVER
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

private:
    int m_socket;
    int m_new_socket;
    std::string m_ip_address;
    unsigned int m_ip_address_len;
    int m_port;
    struct sockaddr_in m_socketAddress;

    void startServer();
    void closeServer();
    void startListen();
    void acceptConnection();
};

#endif