//File này chứa chủ yếu là các hàm nhằm kiểm tra ký tự nhập vào có đúng yêu cầu hay không
//Ngoài ra có một vài hàm hỗ trợ việc in ra màn hình thông báo
#include "helper.h"
#include <string>
#include <regex>

//sử dụng regex để quy định đầu vào cho các phần tử, Tên, email, mã số, nguyên dương .....
bool isValidName(const std::string& str)
{
	std::regex namePattern(R"(^[A-Za-z\s]{1,25}$)");
	return std::regex_match(str, namePattern);
}

bool isValidPersonalKey(const std::string& str)
{
	std::regex idPattern(R"(^\d{8}$)");
	return std::regex_match(str, idPattern);
}

bool isValidEmail(const std::string& str)
{
	std::regex emailPattern(R"(^[a-zA-Z0-9_]{3,}@[a-zA-Z0-9]{3,8}\.[a-zA-Z]{3,}$)");
	return std::regex_match(str, emailPattern);
}


bool isValidUnsignedInt(const std::string& str)
{
	std::regex uIntPattern(R"(^(0*[1-9]\d*)$)");
	return std::regex_match(str, uIntPattern);
}

bool isValidUnsignedInt2(const std::string& str)
{
	std::regex uIntPattern(R"(^(0*[0-9]\d*)$)");
	return std::regex_match(str, uIntPattern);
}

