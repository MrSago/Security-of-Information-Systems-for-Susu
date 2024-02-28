#ifndef _COMMAND_PARSER_H
#define _COMMAND_PARSER_H

#include <functional>
#include <map>
#include <string>

#include "command.h"

using CommandMap = std::map<std::string, Command>;

class CommandParser {
 private:
  CommandMap commands_ = {};

 public:
  CommandParser();
  CommandParser(CommandMap commands);
  bool Parse(const std::string& input);
  void AddCommand(const std::string& command,
                  std::function<void(Arguments&)> func);
  void AddCommand(Command command);
  Command& GetCommand(const std::string& command);

 private:
  Arguments Split(const std::string& input) const;
};

#endif  //_COMMAND_PARSER_H