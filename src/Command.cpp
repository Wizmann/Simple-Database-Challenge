//
// Created by Wizmann on 15/9/14.
//

#include "Command.h"


int CMD_Set::execute(Database& db) {
    uint32_t _pre_value = 0;
    if (db.db_get(_key, _pre_value) == Database::DB_OK) {
        _undo_cmd = new CMD_Set(_key, _pre_value);
    } else {
        _undo_cmd = new CMD_Unset(_key);
    }
    return db.db_set(_key, _value);
}

int CMD_Unset::execute(Database& db) {
    uint32_t value;
    if (db.db_get(_key, value) == Database::DB_OK) {
        _undo_cmd = new CMD_Set(_key, value);
    }
    return db.db_unset(_key);
}
