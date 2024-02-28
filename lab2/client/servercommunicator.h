#ifndef _SERVER_COMMUNICATOR_H
#define _SERVER_COMMUNICATOR_H

#include <windows.h>

#include <string>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

enum class ConnectionStatus { kNotConnected, kConnected };

class ServerCommunicator {
 private:
  const char* kServerName = "MRS4G0-PC";

  char client_name_[256] = {"empty"};
  char server_name_[256] = {"empty"};

  WSAData wsa_;
  sockaddr_in dst_addr_;
  SOCKET socket_;

  bool connected_ = false;

 public:
  ServerCommunicator();
  ~ServerCommunicator();
  ConnectionStatus Connect(const char* ip, short port, const char* login,
                           const char* password);
  void Disconnect();
  ConnectionStatus Send(const std::string& msg);
  ConnectionStatus Listen(char* buffer, int buffer_size);
  bool IsConnected();
};

#endif  // _SERVER_COMMUNICATOR_H
