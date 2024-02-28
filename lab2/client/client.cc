#include "client.h"

Client::Client() { InitParser(); }

void Client::Start() {
  std::cout << "Client started\n";
  std::cout << "Type \"help\" for command list\n";

  while (true) {
    std::cout << "client > ";

    std::string command;
    std::getline(std::cin, command);

    if (command[0] != '!') {
      if (communicator_.IsConnected()) {
        ConnectionStatus status = communicator_.Send(command);
        if (status == ConnectionStatus::kNotConnected) {
          std::cout << "Connection failed\n";
        }
      }
      continue;
    }

    int success = parser_.Parse(command);
    if (!success) {
      continue;
    }

    switch (result_) {
      case CommandResult::kConnected:
        StartSession();
        break;

      case CommandResult::kQuit:
        return;

      case CommandResult::kError:
        std::cout << "Error executing command\n";
        break;

      case CommandResult::kDefault:
      default:
        break;
    }

    result_ = CommandResult::kDefault;
  }
}

void Client::InitParser() {
  parser_.AddCommand("!help",
                     std::bind(&Client::Help, this, std::placeholders::_1));
  parser_.AddCommand("!connect",
                     std::bind(&Client::Connect, this, std::placeholders::_1));
  parser_.AddCommand("!quit",
                     std::bind(&Client::Quit, this, std::placeholders::_1));
}

void Client::Help(Arguments& args) {
  std::cout << "List of client commands:\n";
  std::cout << "!help - print this help\n";
  std::cout << "!connect <ip>:<port> <login> <password> - connect to server\n";
  std::cout << "!quit - exit the program\n";
  result_ = CommandResult::kDefault;
}

void Client::Connect(Arguments& args) {
  if (args.size() < 4) {
    std::cout << "Not enough arguments\n";
    result_ = CommandResult::kError;
    return;
  }

  int tmp;
  short port;
  sscanf(args[1].c_str(), "%d.%d.%d.%d:%i", &tmp, &tmp, &tmp, &tmp, &port);

  char* ip;
  ip = strtok((char*)args[1].c_str(), ":");

  const char* login = args[2].c_str();
  const char* password = args[3].c_str();

  std::cout << "Connecting...";
  ConnectionStatus status = communicator_.Connect(ip, port, login, password);
  if (status == ConnectionStatus::kNotConnected) {
    std::cout << "\nConnection failed\n";
    result_ = CommandResult::kError;
    return;
  }

  std::cout << "\nSuccess!\n";
  result_ = CommandResult::kConnected;
}

void Client::StartSession() {
  auto thread_func = [](LPVOID lp_param) -> DWORD {
    Client* client = reinterpret_cast<Client*>(lp_param);
    return client->RecieiveMessages(lp_param);
  };

  DWORD thread_id;
  HANDLE thread_handle =
      CreateThread(NULL, 0, thread_func, this, 0, &thread_id);
  if (thread_handle == NULL) {
    std::cout << "Failed to create thread\n";
    return;
  }

  WaitForSingleObject(thread_handle, INFINITE);

  CloseHandle(thread_handle);
}

DWORD WINAPI Client::RecieiveMessages(LPVOID lp_param) {
  while (communicator_.IsConnected()) {
    char buffer[1024];
    ConnectionStatus status = communicator_.Listen(buffer, 1024);
    if (status == ConnectionStatus::kNotConnected) {
      return 0;
    }
    std::cout << buffer << '\n';
  }

  return 0;
}

void Client::Quit(Arguments& args) {
  communicator_.Disconnect();
  result_ = CommandResult::kQuit;
}
