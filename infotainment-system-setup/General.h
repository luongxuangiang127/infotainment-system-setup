#pragma once

#include "Setting.h"
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

class General : public Setting {
public:
    General();
    ~General();

    std::string get_language();
    std::string get_timeZone();
    void set_timeZone(std::string data);
    void set_language(std::string data);

private:
    std::string timeZone;
    std::string language;
};
