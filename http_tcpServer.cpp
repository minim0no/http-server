#include <http_tcpServer.hpp>
#include <stdexcept>
#include <iostream>

#define BUFFER_SIZE = 30720;

// constructors/destructors
TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port)
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
TcpServer::~TcpServer()
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

void TcpServer::startServer()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1)
    {
        throw std::runtime_error("Cannot create socket");
    }

    if (bind(m_socket, (sockaddr *)&m_socketAddress, sizeof(m_socketAddress)) == -1)
    {
        throw std::runtime_error("Cannot bind socket to the specified address");
    }
}

void TcpServer::startListen()
{
    if (listen(m_socket, 128) == -1)
    {
        throw std::runtime_error("Failed to listen on the address")
    }

    int bytesReceived;

    while (true)
    {
        std::cout << "====== Waiting for a connection ======" << std::endl;
        acceptConnection();

        char buffer[BUFFER_SIZE];
        bytesReceived = recv(m_new_socket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived == -1)
        {
            throw std::runtime_error("Error receiving data")
        }
        std::cout << "====== Received Request ======" << std::endl;
    }
}

void TcpServer::acceptConnection()
{
    m_new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, sizeof(m_socketAddress));
    if (m_new_socket == -1)
    {
        throw std::runtime_error("Error creating socket while accepting new connection")
    }
}

void TcpServer::closeServer()
{
    if (close(m_socket) == -1)
    {
        throw std::runtime_error("Cannot close socket");
    }
}
