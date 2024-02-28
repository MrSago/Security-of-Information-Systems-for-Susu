#include "command.h"

#include <functional>
#include <string>

Command::Command() = default;

Command::Command(const std::string& command,
                 std::function<void(Arguments&)> func)
    : command_(command), func_(func){};

void Command::Execute(Arguments& args) { func_(args); }

std::string Command::GetCommand() { return command_; }
