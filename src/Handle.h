//
// Created by Wizmann on 15/9/14.
//

#ifndef SIMPLEDBCHALLENGE_HANDLE_H
#define SIMPLEDBCHALLENGE_HANDLE_H

#include <stack>
#include <sstream>

#include "Command.h"
#include "Database.h"

class Handle {
public:
    Handle(Database& db): _db(db) {}

    int execute(std::string& cmd_input) {
        std::stringstream stream(cmd_input);
        if (start_with(cmd_input, "SET")) {
            std::string cmd;
            std::string key;
            uint32_t value;
            stream >> cmd >> key >> value;
            execute(new CMD_Set(key, value));
        } else if (start_with(cmd_input, "GET")) {
            std::string cmd;
            std::string key;
            stream >> cmd >> key;
            execute(new CMD_Get(key));
        } else if (start_with(cmd_input, "UNSET")) {
            std::string cmd;
            std::string key;
            stream >> cmd >> key;
            execute(new CMD_Unset(key));
        } else if (start_with(cmd_input, "NUMEQUALTO")) {
            std::string cmd;
            uint32_t value;
            stream >> cmd >> value;
            execute(new CMD_Numequalto(value));
        } else if (start_with(cmd_input, "BEGIN")) {
            execute(new CMD_Begin());
        } else if (start_with(cmd_input, "ROLLBACK")) {
            execute(new CMD_Rollback);
        } else if (start_with(cmd_input, "COMMIT")) {
            execute(new CMD_Commit);
        } else if (start_with(cmd_input, "END")) {
            execute(new CMD_End());
        }
        return 0;
    }
private:
    int execute(Command* cmd) {
        auto ptr = std::shared_ptr<Command>(cmd);
        return execute(ptr);
    }

    int execute(std::shared_ptr<Command> cmd) {
        if (cmd->name() == Command::CMD_BEGIN) {
            _cmd_stack.push(cmd);
            return 0;
        }
        if (cmd->name() == Command::CMD_ROLLBACK || cmd->name() == Command::CMD_COMMIT) {
            if (_cmd_stack.empty()) {
                Printer::get_instance().print("NO TRANSACTION");
                return 0;
            }
        }
        if (cmd->name() == Command::CMD_ROLLBACK) {
            while (true) {
                auto prev_cmd = _cmd_stack.top();
                _cmd_stack.pop();
                prev_cmd->undo(_db);
                if (prev_cmd->name() == Command::CMD_BEGIN) {
                    break;
                }
            }
            return 0;
        }
        if (cmd->name() == Command::CMD_COMMIT) {
            while (!_cmd_stack.empty()) {
                auto prev_cmd = _cmd_stack.top();
                _cmd_stack.pop();
            }
            return 0;
        }
        cmd->execute(_db);
        if (!_cmd_stack.empty()) {
            _cmd_stack.push(cmd);
        }
        return 0;
    }

    bool start_with(const std::string& haystack, const std::string& needle) {
        return haystack.substr(0, needle.size()) == needle;
    }
private:
    Database& _db;
    std::stack<std::shared_ptr<Command> > _cmd_stack;
};


#endif //SIMPLEDBCHALLENGE_HANDLE_H
