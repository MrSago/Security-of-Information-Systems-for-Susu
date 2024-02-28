#include "commandparser.h"

#include <functional>
#include <sstream>
#include <string>

CommandParser::CommandParser() = default;

CommandParser::CommandParser(CommandMap commands) : commands_(commands){};

bool CommandParser::Parse(const std::string& input) {
  Arguments tokens = Split(input);

  if (tokens.empty()) {
    return false;
  }

  const std::string& command = tokens[0];
  if (commands_.find(command) == commands_.end()) {
    return false;
  }
  commands_[command].Execute(tokens);

  return true;
}

void CommandParser::AddCommand(const std::string& command,
                               std::function<void(Arguments&)> func) {
  commands_.insert({command, Command(command, func)});
}

void CommandParser::AddCommand(Command command) {
  commands_.insert({command.GetCommand(), command});
}

Command& CommandParser::GetCommand(const std::string& command) {
  return commands_[command];
}

Arguments CommandParser::Split(const std::string& input) const {
  std::istringstream stream(input);
  Arguments tokens;
  std::string token;

  while (std::getline(stream, token, ' ')) {
    tokens.push_back(token);
  }

  return tokens;
}
