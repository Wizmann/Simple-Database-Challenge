#include <iostream>

#include "src/Database.h"
#include "src/Handle.h"

using namespace std;

int main() {
    string buffer;
    Database db;
    Handle handle(db);
    while (std::getline(cin, buffer)) {
        handle.execute(buffer);
    }
    return 0;
}