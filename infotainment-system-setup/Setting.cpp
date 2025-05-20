#include "Setting.h"
#include "helper.h"
#include <string>

Setting::Setting()
{
    owner_name = "N/A";
    personal_key = "N/A";
    email = "N/A";
    odo = 0;
    service_remind = 0;
}

Setting::~Setting() {

}
//setters
void Setting::setOwnerName(const std::string& str)
{
    owner_name = str;
}
void Setting::setEmail(const std::string& str)
{
    email = str;
}
void Setting::setPersonalKey(const std::string& str)
{
    personal_key = str;
}
void Setting::setODO(int num)
{
    odo = num;
}
void Setting::setServiceRemind(int num)
{
    service_remind = num;
}
//getters
std::string Setting::getOwnerName() {
    return owner_name;
}

std::string Setting::getEmail() {
    return email;
}

std::string Setting::getPersonalKey() {
    return personal_key;
}

int Setting::getODO() {
    return odo;
}

int Setting::getServiceRemind() {
    return service_remind;
}

void Setting::nhapThongTin() {
    std::string ten;
    std::string emailStr;
    std::string personal_key_str;
    std::string soODO;
    std::string soRemind;
    std::cout << "    Owner name: ";
    while (true)                        //Kiêm tra đầu vào cho các phần tử
    {
        std::getline(std::cin, ten);

        if (isValidName(ten))
        {
            owner_name = ten;
            break;
        }
        else
        {
            std::cout << "    -> Invalid name, please enter again: ";
            
        }
    }
    
    std::cout << "    Email: ";
    while (true)
    {
        std::getline(std::cin, emailStr);

        if (isValidEmail(emailStr))
        {
            email = emailStr;
            break;
        }
        else
        {
            std::cout << "    -> Invalid email, please enter again: ";
            
        }
    }
   
    std::cout << "    Key number: ";
    while (true)
    {
        std::getline(std::cin, personal_key_str);

        if (isValidPersonalKey(personal_key_str))
        {
            personal_key = personal_key_str;
            break;
        }
        else
        {
            std::cout << "    -> Invalid personal key, please enter again: ";
            
        }
    }


    std::cout << "    ODO number (km): ";
    while (true)
    {
        std::getline(std::cin, soODO);

        if (isValidUnsignedInt(soODO))
        {
            odo = std::stoi(soODO);
            break;
        }
        else
        {
            std::cout << "    -> Invalid ODO number, please enter again: ";
            
        }
    }
    std::cout << "    Remind service (km): ";
    while (true)
    {
        std::getline(std::cin, soRemind);

        if (isValidUnsignedInt(soRemind))
        {
            service_remind = std::stoi(soRemind);
            break;
        }
        else
        {
            std::cout << "    -> Invalid remind service number, please enter again: ";
            
        }
    }

}


