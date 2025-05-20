#include "Sound.h"
#include "helper.h"
#include <string>

Sound::Sound(): Setting()
{
    media_level = 0;
    call_level = 0;
    navi_level = 0;
    notification_level = 0;
}

Sound::~Sound(){
	
}

//Nhập thông tin sound
void Sound::nhapThongTin(){
    std::string media;
    std::string call;
    std::string navi;
    std::string notification;

    std::cout << "    Media level: ";
    while (true)                     //Kiểm tra phần tử nhập vào, tương tự với những phần tử sau
    {
        std::getline(std::cin, media);

        if (isValidUnsignedInt(media))
        {
            media_level = std::stoi(media);
            break;
        }
        else
        {
            std::cout << "    -> Invalid media level number, please enter again: ";

        }
    }


    std::cout << "    Call level: ";
    while (true)
    {
        std::getline(std::cin, call);

        if (isValidUnsignedInt(call))
        {
            call_level = std::stoi(call);
            break;
        }
        else
        {
            std::cout << "    -> Invalid call level number, please enter again: ";

        }
    }
    std::cout << "    Navi level: ";
    while (true)
    {
        std::getline(std::cin, navi);

        if (isValidUnsignedInt(navi))
        {
            navi_level = std::stoi(navi);
            break;
        }
        else
        {
            std::cout << "    -> Invalid navi level number, please enter again: ";

        }
    }
   
    std::cout << "    Notification level: ";
    while (true)
    {
        std::getline(std::cin, notification);

        if (isValidUnsignedInt(notification))
        {
            notification_level = std::stoi(notification);
            break;
        }
        else
        {
            std::cout << "    -> Invalid notification level number, please enter again: ";

        }
    }
    
}

//getters
int Sound::get_media_level(){
    return media_level;
}

int Sound::get_call_level(){
    return call_level;
}

int Sound::get_navi_level(){
    return navi_level;
}

int Sound::get_notification_level(){
    return notification_level;
}

//setters
void Sound::set_media_level(int data){
    media_level = data;
}

void Sound::set_call_level(int data){
    call_level = data;
}

void Sound::set_navi_level(int data){
    navi_level = data;
}

void Sound::set_notification_level(int data){
    notification_level = data;
}

