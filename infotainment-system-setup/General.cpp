#include "General.h"

General::General()
{
    timeZone = "N/A";
    language = "N/A";
}

General::~General() {

}

//getter
std::string General::get_language() {
    return language;
}

std::string General::get_timeZone() {
    return timeZone;
}

//setter
void General::set_timeZone(std::string data) {
    timeZone = data;
}

void General::set_language(std::string data) {
    language = data;
}
