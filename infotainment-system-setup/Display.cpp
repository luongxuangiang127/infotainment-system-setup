#include "Display.h"
#include <string>
#include "helper.h"

Display::Display(): Setting()
{
    light_level = 0;
    screen_light_level = 0;
    taplo_light_level = 0;
}

Display::~Display(){
}
//getters
int Display::get_light_level(){
    return light_level;
}

int Display::get_screen_light_level(){
    return screen_light_level;
}

int Display::get_taplo_light_level(){
    return taplo_light_level;
}
//setters
void Display::set_light_level(int data){
    light_level = data;
}

void Display::set_screen_light_level(int data){
    screen_light_level = data;
}

void Display::set_taplo_light_level(int data){
    taplo_light_level = data;
}

void Display::nhapThongTin(){
    
    std::string light;
    std::string screen;
    std::string taplo;

    std::cout << "    Light level: ";
    while (true)                            //kiểm tra phần tử nhập vào, tương tự với những phần tử sau
    {
        std::getline(std::cin, light);

        if (isValidUnsignedInt(light))
        {
            light_level = std::stoi(light);
            break;
        }
        else
        {
            std::cout << "    -> Invalid light level number, please enter again: ";

        }
    }
  
    std::cout << "    Screen light level: ";
    while (true)
    {
        std::getline(std::cin, screen);

        if (isValidUnsignedInt(screen))
        {
            screen_light_level = std::stoi(screen);
            break;
        }
        else
        {
            std::cout << "    -> Invalid screen light level number, please enter again: ";

        }
    }
    std::cout << "    Taplo light level: ";
    while (true)
    {
        std::getline(std::cin, taplo);

        if (isValidUnsignedInt(taplo))
        {
            taplo_light_level = std::stoi(taplo);
            break;
        }
        else
        {
            std::cout << "    -> Invalid taplo level number, please enter again: ";

        }
    }
 
}

