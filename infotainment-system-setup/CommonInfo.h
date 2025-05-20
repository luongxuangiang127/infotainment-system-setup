#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <iomanip>
#include <string>

class CommonInfo {
public:
    std::string getNumber() {
        return number;
    }

    std::string getName() {
        return name;
    }

    void setNumber(std::string data) {
        number = data;
    }

    void setName(std::string data) {
        name = data;
    }

    void printData() {
        std::cout<<std::left << std::setw(2) << number << ": "
            << std::setw(15) << name << std::endl;
    }

private:
    std::string number;
    std::string name;
};

#endif // COMMON_H_
