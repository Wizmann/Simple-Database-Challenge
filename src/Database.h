//
// Created by Wizmann on 15/9/14.
//

#ifndef SIMPLEDBCHALLENGE_DATABASE_H
#define SIMPLEDBCHALLENGE_DATABASE_H

#include <cstring>
#include <string>
#include <unordered_map>

class Database {
public:
    enum {
        DB_OK = 0,
        DB_NOT_FOUND = 1,
        DB_ERROR = 255,
    };
public:
    Database() {}
    int db_set(const std::string& key, const uint32_t& value) {
        auto iter = _db.find(key);
        if (iter != _db.end()) {
            _counter[iter->second]--;
        }

        _db[key] = value;
        _counter[value]++;
        return DB_OK;
    }
    int db_get(const std::string& key, uint32_t& value) {
        auto iter = _db.find(key);
        if (iter == _db.end()) {
            return DB_NOT_FOUND;
        }
        value = iter->second;
        return DB_OK;
    }
    int db_unset(const std::string& key) {
        auto iter = _db.find(key);
        if (iter == _db.end()) {
            return DB_NOT_FOUND;
        }
        _counter[iter->second]--;
        _db.erase(iter);
        return DB_OK;
    }
    int db_num_equal_to(const uint32_t value, uint32_t& res) {
        res = _counter[value];
        if (res != 0) {
            return DB_OK;
        } else {
            return DB_NOT_FOUND;
        }
    }
private:
    std::unordered_map<std::string, uint32_t> _db;
    std::unordered_map<uint32_t, uint32_t> _counter;
};


#endif //SIMPLEDBCHALLENGE_DATABASE_H
