#include <http_tcpServer.hpp>
#include <stdexcept>

class TcpServer
{
    // constructors/destructors
    TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port)
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());

        try
        {
            startServer();
        }
        catch (const std::exception &e)
        {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            std::cerr << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port) << std::endl;
            exit(0);
        }
    }
    ~TcpServer()
    {
        try
        {
            closeServer();
        }
        catch (const std::exception &e)
        {
            std::cerr << "An error occurred: " << e.what() << std::endl;
        }
        exit(0);
    }

    void startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket == -1)
        {
            throw std::runtime_error("Cannot create socket");
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, sizeof(m_socketAddress)) == -1)
        {
            throw std::runtime_error("Cannot bind socket");
        }
    }

    void closeServer()
    {
        if (close(m_socket) == -1)
        {
            throw std::runtime_error("Cannot close socket");
        }
    }
};
