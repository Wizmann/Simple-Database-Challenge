//
// Created by Wizmann on 15/9/14.
//

#ifndef SIMPLEDBCHALLENGE_PRINTER_H
#define SIMPLEDBCHALLENGE_PRINTER_H

#include <iostream>

class Printer {
public:
    static Printer& get_instance() {
        static Printer printer;
        return printer;
    }

    template <typename T>
    void print(const T& item) {
        std::cout << item << std::endl;
    }
private:
    Printer() {}
    Printer(const Printer& printer);
    Printer& operator=(const Printer& printer);
};


#endif //SIMPLEDBCHALLENGE_PRINTER_H
