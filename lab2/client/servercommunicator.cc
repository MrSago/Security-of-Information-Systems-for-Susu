#include "servercommunicator.h"

#include <iostream>

// #include "cryptopp/filters.h"
// #include "cryptopp/hex.h"
// #include "cryptopp/md5.h"

ServerCommunicator::ServerCommunicator() {
  WSAStartup(0x0202, &wsa_);
  gethostname(client_name_, 256);
}

ServerCommunicator::~ServerCommunicator() {
  Disconnect();
  WSACleanup();
}

ConnectionStatus ServerCommunicator::Connect(const char* ip, short port,
                                             const char* login,
                                             const char* password) {
  if (connected_) {
    return ConnectionStatus::kNotConnected;
  }

  dst_addr_.sin_family = AF_INET;
  dst_addr_.sin_addr.s_addr = inet_addr(ip);
  dst_addr_.sin_port = htons(port);

  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  int code = connect(socket_, reinterpret_cast<sockaddr*>(&dst_addr_),
                     sizeof(dst_addr_));
  if (code == SOCKET_ERROR) {
    closesocket(socket_);
    return ConnectionStatus::kNotConnected;
  }

  send(socket_, client_name_, strlen(client_name_), 0);
  recv(socket_, server_name_, strlen(server_name_), 0);
  if (strcmp(kServerName, server_name_)) {
    closesocket(socket_);
    return ConnectionStatus::kNotConnected;
  }

  // std::string password_hash;
  // CryptoPP::MD5 hash;
  // CryptoPP::StringSource ss(
  //     password, true,
  //     new CryptoPP::HashFilter(
  //         hash,
  //         new CryptoPP::HexEncoder(new
  //         CryptoPP::StringSink(password_hash))));

  send(socket_, login, strlen(login), 0);
  send(socket_, password, strlen(password), 0);

  char answer[256];
  recv(socket_, answer, 256, 0);
  if (strcmp("OK", answer)) {
    closesocket(socket_);
    return ConnectionStatus::kNotConnected;
  }

  connected_ = true;
  return ConnectionStatus::kConnected;
}

void ServerCommunicator::Disconnect() {
  connected_ = false;
  closesocket(socket_);
}

ConnectionStatus ServerCommunicator::Send(const std::string& msg) {
  if (!connected_) {
    return ConnectionStatus::kNotConnected;
  }

  int code = send(socket_, msg.c_str(), msg.size(), 0);
  if (code == SOCKET_ERROR) {
    connected_ = false;
    return ConnectionStatus::kNotConnected;
  }

  return ConnectionStatus::kConnected;
}

ConnectionStatus ServerCommunicator::Listen(char* buffer, int buffer_size) {
  if (!connected_) {
    connected_ = false;
    return ConnectionStatus::kNotConnected;
  }
  int code = recv(socket_, buffer, buffer_size, 0);
  if (code == SOCKET_ERROR) {
    connected_ = false;
    return ConnectionStatus::kNotConnected;
  }

  return ConnectionStatus::kConnected;
}

bool ServerCommunicator::IsConnected() { return connected_; }