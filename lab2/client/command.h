#ifndef _COMMAND_H
#define _COMMAND_H

#include <functional>
#include <map>
#include <string>
#include <vector>

using Arguments = std::vector<std::string>;

class Command {
 private:
  const std::string command_;
  std::function<void(Arguments&)> func_;

 public:
  Command();
  Command(const std::string& command, std::function<void(Arguments&)> func);
  void Execute(Arguments& args);
  std::string GetCommand();
};

#endif  //_COMMAND_H
