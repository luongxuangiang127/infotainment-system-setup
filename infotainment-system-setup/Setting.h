#ifndef SETTING_H_
#define SETTING_H_

#include <iostream>
#include <iomanip>
#include <string>

class Setting {
public:
    Setting();
    virtual ~Setting();
    void nhapThongTin();
  
    std::string getOwnerName();
    std::string getEmail();
    std::string getPersonalKey();
    int getODO();
    int getServiceRemind();

    void setOwnerName(const std::string& str);
    void setEmail(const std::string& str);
    void setPersonalKey(const std::string& str);
    void setODO(int num);
    void setServiceRemind(int num);

private:
    std::string owner_name;
    std::string personal_key; 	// Chuoi 8 ky tu so
    std::string email;			// email format abc@xyz.com
    int odo;
    int service_remind;
};

#endif /* SETTING_H_ */
