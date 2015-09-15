//
// Created by Wizmann on 15/9/14.
//

#ifndef SIMPLEDBCHALLENGE_COMMAND_H
#define SIMPLEDBCHALLENGE_COMMAND_H

#include <algorithm>
#include <string>

#include "Database.h"
#include "Printer.h"

class Command {
public:
    enum {
        CMD_SET,
        CMD_GET,
        CMD_UNSET,
        CMD_NUMEQUALTO,
        CMD_BEGIN,
        CMD_COMMIT,
        CMD_ROLLBACK,
        CMD_END
    };
public:
    virtual int name() = 0;
    virtual std::string verbose() = 0;
    virtual int execute(Database& db) = 0;
    virtual int undo(Database& db) = 0;
    virtual ~Command() {}
};

class CMD_Set: public Command {
public:
    CMD_Set(const std::string& key, uint32_t value): \
            _key(key),
            _value(value),
            _undo_cmd(nullptr) {}

    virtual int name() {
        return CMD_SET;
    }

    virtual std::string verbose() {
        return "SET: " + _key + " " + std::to_string(_value);
    }

    virtual int execute(Database& db);

    virtual int undo(Database& db) {
        if (_undo_cmd == nullptr) {
            return Database::DB_ERROR;
        }
        return _undo_cmd->execute(db);
    }
private:
    std::string _key;
    uint32_t _value;
    std::shared_ptr<Command> _undo_cmd;
};

class CMD_Get: public Command {
public:
    CMD_Get(const std::string& key): _key(key) {};

    virtual int name() {
        return CMD_GET;
    }

    virtual std::string verbose() {
        return "GET " + _key;
    }

    virtual int execute(Database& db) {
        uint32_t value = 0;
        int res = db.db_get(_key, value);
        if (res == Database::DB_NOT_FOUND) {
            Printer::get_instance().print("NULL");
        } else {
            Printer::get_instance().print(value);
        }
        return res;
    }

    virtual int undo(Database& db) {
        return Database::DB_OK;
    }
private:
    std::string _key;
};

class CMD_Numequalto: public Command {
public:
    CMD_Numequalto(const uint32_t value): _value(value) {}
    virtual int name() {
        return CMD_NUMEQUALTO;
    }
    virtual std::string verbose() {
        return "NUMEQUALTO " + std::to_string(_value);
    }
    virtual int execute(Database& db) {
        uint32_t cnt = 0;
        int res = db.db_num_equal_to(_value, cnt);
        Printer::get_instance().print(cnt);
        return res;
    }
    virtual int undo(Database& db) {
        return Database::DB_OK;
    }
private:
    uint32_t _value;
};

class CMD_Unset: public Command {
public:
    CMD_Unset(const std::string& key): _key(key), _undo_cmd(nullptr) {}

    virtual int name() {
        return CMD_UNSET;
    }

    virtual std::string verbose() {
        return "UNSET " + _key;
    }

    virtual int execute(Database& db);

    virtual int undo(Database& db) {
        if (_undo_cmd == nullptr) {
            return Database::DB_ERROR;
        }
        return _undo_cmd->execute(db);
    }
private:
    std::string _key;
    std::shared_ptr<Command> _undo_cmd;
};

class CMD_Dummy: public Command {
public:
    virtual int execute(Database& db) {
        return Database::DB_OK;
    }
    virtual int undo(Database& db) {
        return Database::DB_OK;
    }
};

class CMD_Begin: public CMD_Dummy {
public:
    virtual int name() {
        return Command::CMD_BEGIN;
    }
    virtual std::string verbose() {
        return "BEGIN";
    }
};

class CMD_Commit: public CMD_Dummy {
public:
    virtual int name() {
        return Command::CMD_COMMIT;
    }
    virtual std::string verbose() {
        return "COMMIT";
    }
};

class CMD_Rollback: public CMD_Dummy {
public:
    virtual int name() {
        return Command::CMD_ROLLBACK;
    }
    virtual std::string verbose() {
        return "ROLLBACK";
    }
};

class CMD_End: public CMD_Dummy {
public:
    virtual int name() {
        return Command::CMD_END;
    }
    virtual std::string verbose() {
        return "END";
    }
};

#endif //SIMPLEDBCHALLENGE_COMMAND_H
