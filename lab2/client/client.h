#ifndef _CLIENT_H
#define _CLIENT_H

#include <windows.h>

#include <iostream>

#include "command.h"
#include "commandparser.h"
#include "servercommunicator.h"

enum class CommandResult {
  kDefault,
  kError,
  kConnected,
  kQuit,
};

class Client {
 private:
  ServerCommunicator communicator_;
  CommandParser parser_;
  CommandResult result_ = CommandResult::kDefault;

 public:
  Client();
  void Start();

 private:
  void InitParser();
  void StartSession();
  DWORD WINAPI RecieiveMessages(LPVOID lp_param);

  void Help(Arguments& args);
  void Connect(Arguments& args);
  void Quit(Arguments& args);
};

#endif  // _CLIENT_H
