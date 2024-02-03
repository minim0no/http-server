#include <http_tcpServer.hpp>
#include <stdexcept>

class TcpServer {
    // constructors/destructors
    TcpServer::TcpServer() {}
    TcpServer::~TcpServer(){
        closeServer();
        exit(0);
    }

    TcpServer::startServer() {
        try {
            mSocket = socket(AF_INET, SOCK_STREAM, 0)
            if (mSocket == -1) {
                throw std::runtime_error("Cannot create socket");
            }
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            exit(1);
        }
    }
    
    TcpServer::closeServer() {
        try {
            if (close(mSocket) == -1) {
                throw std::runtime_error("Cannot close socket");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
            exit(1);
        }
    }
}