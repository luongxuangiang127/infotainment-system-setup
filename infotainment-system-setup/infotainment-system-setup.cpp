//khai báo thư viện
#include <iostream>
#include "General.h"
#include "Display.h"
#include "Sound.h"
#include "CommonInfo.h"
#include <fstream>
#include "list.h"
#include <string>
#include <iomanip>
#include "Setting.h"
#include <sstream>
#include <regex>
#include <algorithm>
#include "helper.h"
using namespace std;

// Ban can tao ra 3 list luu tru du lieu cho Display, Sound, General voi class Template List
List<Setting*> display;
List<Setting*> sound;
List<Setting*> general;

int carCount = 0;

vector<CommonInfo> timezoneList;
vector<CommonInfo> languageList;

void NhapThongTinCaiDat();
void XuatThongTinCaiDat();

void XuatThongTinCaiDat_Sound();
void XuatThongTinCaiDat_General();
void XuatThongTinCaiDat_Display();
void XuatThongTatCaTinCaiDat();

void NhapThongTinCaiDat_Sound();
void NhapThongTinCaiDat_General();
void NhapThongTinCaiDat_Display();

void downloadTimeZone();
void downloadLanguage();
void downloadSettings();
void uploadSettings();

int searchKey(const List<Setting*>& arr, int num, const string& str);
void copySettingInfo(Setting* info1, Setting* info2, Setting* info3);
string rutGonTimeZone(const string& str);
string rutGonLanguage(const string& str);

void sapXep(List<Setting*>& listArr);

void menu();

// ========= HÀM MAIN ============

int main(int argc, char** argv)
{
	//Lưu nội dung các file vào list hoặc vector
	downloadLanguage();
	downloadTimeZone();
	downloadSettings();

	//đi đến menu chính, rồi từ menu chính sẽ rẽ sang những hướng khác
	menu();

	//lưu thông tin từ các list vào file settings.txt
	uploadSettings();
	return 0;
}// ========= CÁC MÀN HÌNH ================
// ---- màn hình Main Menu -----
void menu()
{
	system("cls");
	cout << " --- SELECT MENU ---" << endl;
	cout << " 1. Input setting information" << endl;
	cout << " 2. Print setting information" << endl;
	cout << " 3. Exit" << endl;
	cout << " Your selection: ";

	string selection;

	while (true)
	{
		std::getline(cin, selection);
		if (selection == "1")
		{
			NhapThongTinCaiDat();
			break;
		}
		else if (selection == "2")
		{
			XuatThongTinCaiDat();
			break;
		}
		else if (selection == "3")
		{
			system("cls");
			cout << " Thank you for using the program..." << endl << endl;
			system("pause");
			break;
		}
		else
		{
			cout << " -> Invalid selection, please enter again ( 1 -> 3 ): ";

		}
	}

}

//======= Màn hình nhập thông tin cài đặt =========
void NhapThongTinCaiDat()
{
	system("cls");
	cout << " --- SELECT MENU ---" << endl;
	cout << " 1. Display setting" << endl;
	cout << " 2. Sound setting" << endl;
	cout << " 3. General setting" << endl;
	cout << " 0. Back to previous screen" << endl;
	cout << " Your selection: ";

	string selection;

	while (true)
	{
		std::getline(cin, selection);
		if (selection == "1")
		{
			NhapThongTinCaiDat_Display();
			break;
		}
		else if (selection == "2")
		{
			NhapThongTinCaiDat_Sound();
			break;
		}
		else if (selection == "3")
		{
			NhapThongTinCaiDat_General();
			break;
		}
		else if (selection == "0")
		{
			menu();
			break;
		}
		else
		{
			cout << " -> Invalid selection, please enter again ( 0 -> 3 ): ";
		}

	}

}

//--------- lựa chọn cài đặt sound ----------
void NhapThongTinCaiDat_Sound()
{
	string choice;
	do
	{
		system("cls");
		cout << " --- Input Sound setting --- " << endl;

		cout << " Car index: " << carCount + 1 << endl;

		Setting* sD = new Display();  //khởi tạo 3 con trỏ setting đến 3 class khác nhau
		Setting* sS = new Sound();
		Setting* sG = new General();


		sS->nhapThongTin();			  //nhập thông tin common

		copySettingInfo(sS, sD, sG);  //copy thông tin common sang những địa chỉ khác

		int k = searchKey(sound, carCount, sS->getPersonalKey());   // tìm xem xe đã xuất hiện hay chưa

		if (k == -1) {
			cout << "        -> This is a new car, data will be appended to your list" << endl;
		}
		else {
			cout << "        -> This car already existed, data will be overriten" << endl;
		}


		static_cast<Sound*>(sS)->nhapThongTin();  //ép kiểu để nhập đến những thông tin cài đặt sound

		if (k == -1) {                           //Nếu xe mới, thêm thành viên mới cho các list 
			display.add(sD, carCount);
			sound.add(sS, carCount);
			general.add(sG, carCount);
			carCount++;
		}
		else {										//nếu xe đã xuất hiện, copy cài đặt sound vào vị trí trùng lặp								
			sound.add(sS, k);
			copySettingInfo(sS, display.get(k), general.get(k));  //cập nhật thông tin chung cho các xe cùng vị trí
		}

		//sắp xếp lại các list
		sapXep(display);
		sapXep(sound);
		sapXep(general);

		cout << endl;

		cout << " -> Will you input for Car " << carCount + 1 << " ? (y/n): ";
		do
		{
			getline(cin, choice);
			cout << " Invalid language number, please enter again (y/n) or (Y/N): ";
		} while (choice != "y" && choice != "Y" && choice != "n" && choice != "N");

	} while (choice == "Y" || choice == "y");

	NhapThongTinCaiDat();
}

//----------Nhập thông tin cài đặt General -------
void NhapThongTinCaiDat_General()
{
	string choice;
	do
	{
		system("cls");
		cout << " --- Input General setting --- " << endl;
		cout << " Car index: " << carCount + 1 << endl;

		Setting* sD = new Display();
		Setting* sS = new Sound();
		Setting* sG = new General();


		sG->nhapThongTin();

		copySettingInfo(sG, sD, sS);

		int k = searchKey(general, carCount, sG->getPersonalKey());

		if (k == -1) {
			cout << "        -> This is a new car, data will be appended to your list" << endl;
		}
		else {
			cout << "        -> This car already existed, data will be overriten" << endl;
		}
		system("pause");
		system("cls");
		//Select timezone data
		cout << " --- Select timezone data ---" << endl;
		for (int i = 0; i < timezoneList.size();i++)     // in timezone list từ file
		{
			timezoneList[i].printData();
		}
		cout << " Your selection: ";

		string time;
		while (true)
		{
			std::getline(std::cin, time);

			if (isValidUnsignedInt(time) && stoi(time) <= timezoneList.size())
			{
				static_cast<General*>(sG)->set_timeZone(timezoneList[stoi(time) - 1].getName());
				break;
			}
			else
			{
				std::cout << "    -> Invalid time zone number, please enter again: ";
			}
		}

		cout << endl;
		system("pause");
		system("cls");
		//Select language data
		cout << " --- select language data ---" << endl;
		for (int i = 0; i < languageList.size();i++)      // in language list từ file
		{
			languageList[i].printData();
		}

		cout << " Your selection: ";

		string lang;
		while (true)
		{
			std::getline(std::cin, lang);

			if (isValidUnsignedInt(lang) && stoi(lang) <= languageList.size())
			{
				static_cast<General*>(sG)->set_language(languageList[stoi(lang) - 1].getName());
				break;
			}
			else
			{
				std::cout << "    -> Invalid language number, please enter again: ";
			}
		}

		if (k == -1) {
			display.add(sD, carCount);
			sound.add(sS, carCount);
			general.add(sG, carCount);
			carCount++;
		}
		else {
			general.add(sG, k);
			copySettingInfo(sG, display.get(k), sound.get(k));
		}

		//sắp xếp lại các list
		sapXep(display);
		sapXep(sound);
		sapXep(general);

		cout << endl;

		cout << " -> Will you input for Car " << carCount + 1 << " ? (y/n): ";
		do
		{
			getline(cin, choice);
			cout << " Invalid language number, please enter again (y/n) or (Y/N): ";
		} while (choice != "y" && choice != "Y" && choice != "n" && choice != "N");

	} while (choice == "Y" || choice == "y");

	NhapThongTinCaiDat();
}

//---------------Nhập thông tin display--------------------
void NhapThongTinCaiDat_Display()
{
	//tương tự như nhập thông tin cài đặt sound
	string choice;
	do
	{
		system("cls");
		cout << " --- Input Display setting --- " << endl;
		cout << " Car index: " << carCount + 1 << endl;

		Setting* sD = new Display();
		Setting* sS = new Sound();
		Setting* sG = new General();


		sD->nhapThongTin();

		copySettingInfo(sD, sS, sG);

		int k = searchKey(display, carCount, sD->getPersonalKey());

		if (k == -1) {
			cout << "        -> This is a new car, data will be appended to your list" << endl;
		}
		else {
			cout << "        -> This car already existed, data will be overriten" << endl;
		}


		static_cast<Display*>(sD)->nhapThongTin();


		if (k == -1) {
			display.add(sD, carCount);
			sound.add(sS, carCount);
			general.add(sG, carCount);
			carCount++;
		}
		else {
			display.add(sD, k);
			copySettingInfo(sD, general.get(k), sound.get(k));
		}


		sapXep(display);
		sapXep(sound);
		sapXep(general);

		cout << endl;

		cout << " -> Will you input for Car " << carCount + 1 << " ? (y/n): ";
		do
		{
			getline(cin, choice);
			cout << " Invalid language number, please enter again (y/n) or (Y/N): ";
		} while (choice != "y" && choice != "Y" && choice != "n" && choice != "N");

	} while (choice == "Y" || choice == "y");

	NhapThongTinCaiDat();
}


//============== màn hình xuất thông tin ==================
void XuatThongTinCaiDat() {

	system("cls");
	cout << " --- SELECT MENU ---" << endl;
	cout << " 1. Print Display setting information" << endl;
	cout << " 2. Print Sound setting information" << endl;
	cout << " 3. Print General setting information" << endl;
	cout << " 4. Print All setting information" << endl;
	cout << " 0. Back to previous screen" << endl;
	cout << " Your selection: ";
	string selection;


	while (true)
	{
		std::getline(cin, selection);

		if (selection == "1")
		{
			system("cls");
			cout << " --- Display setting --- " << endl;
			XuatThongTinCaiDat_Display();
			break;
		}
		else if (selection == "2")
		{
			system("cls");
			cout << " --- Sound setting --- " << endl;
			XuatThongTinCaiDat_Sound();
			break;
		}
		else if (selection == "3")
		{
			system("cls");
			cout << " --- Thong tin General --- " << endl;
			XuatThongTinCaiDat_General();
			break;
		}
		else if (selection == "4")
		{
			system("cls");
			cout << " --- All settings --- " << endl;
			XuatThongTatCaTinCaiDat();
			break;
		}
		else if (selection == "0")
		{
			menu();
			break;
		}
		else
		{
			cout << " -> Invalid selection, please enter again ( 0 -> 4 ): ";
		}
	}
}



//-------- Xuất thông tin cài đặt Sound ------

void XuatThongTinCaiDat_Sound()
{

	cout << " " << left << setw(20) << "Owner name"
		<< setw(35) << "Email"
		<< setw(20) << "Key number"
		<< setw(20) << "ODO number"
		<< setw(20) << "Remind service (km)"
		<< setw(20) << "Call level"
		<< setw(20) << "Media level"
		<< setw(20) << "Navi level"
		<< setw(20) << "Notification level" << endl;
	for (int i = 0; i < carCount;i++)
	{
		Sound* soundLevels = static_cast<Sound*>(sound.get(i));

		cout << " " << left << setw(20) << sound.get(i)->getOwnerName()
			<< setw(35) << sound.get(i)->getEmail()
			<< setw(20) << sound.get(i)->getPersonalKey()
			<< setw(20) << sound.get(i)->getODO()
			<< setw(20) << sound.get(i)->getServiceRemind()

			<< setw(20) << soundLevels->get_call_level()
			<< setw(20) << soundLevels->get_media_level()
			<< setw(20) << soundLevels->get_navi_level()
			<< setw(20) << soundLevels->get_notification_level() << endl;
	}
	cout << endl;
	system("pause");
	XuatThongTinCaiDat();
}

//-------- Xuất thông tin cài đặt General -------
void XuatThongTinCaiDat_General()
{
	cout << " " << left << setw(20) << "Owner name"
		<< setw(35) << "Email"
		<< setw(20) << "Key number"
		<< setw(20) << "ODO number"
		<< setw(20) << "Remind service (km)"
		<< setw(20) << "Time zone"
		<< setw(20) << "Language" << endl;
	for (int i = 0; i < carCount;i++)
	{
		General* generalSettings = static_cast<General*>(general.get(i));
		cout << " " << left << setw(20) << display.get(i)->getOwnerName()
			<< setw(35) << display.get(i)->getEmail()
			<< setw(20) << display.get(i)->getPersonalKey()
			<< setw(20) << display.get(i)->getODO()
			<< setw(20) << display.get(i)->getServiceRemind()

			<< setw(20) << rutGonTimeZone(generalSettings->get_timeZone())
			<< setw(20) << generalSettings->get_language() << endl;
	}
	cout << endl;
	system("pause");
	XuatThongTinCaiDat();

}


//-------- Xuất thông tin cài đặt Display --------
void XuatThongTinCaiDat_Display() {

	cout << " " << left << setw(20) << "Owner name"
		<< setw(35) << "Email"
		<< setw(20) << "Key number"
		<< setw(20) << "ODO number"
		<< setw(20) << "Remind service (km)"
		<< setw(20) << "Light level"
		<< setw(20) << "Taplo light"
		<< setw(20) << "Screen light" << endl;
	for (int i = 0; i < carCount;i++)
	{
		Display* displayLevels = static_cast<Display*>(display.get(i));

		cout << " " << left << setw(20) << display.get(i)->getOwnerName()
			<< setw(35) << display.get(i)->getEmail()
			<< setw(20) << display.get(i)->getPersonalKey()
			<< setw(20) << display.get(i)->getODO()
			<< setw(20) << display.get(i)->getServiceRemind()

			<< setw(20) << displayLevels->get_light_level()
			<< setw(20) << displayLevels->get_taplo_light_level()
			<< setw(20) << displayLevels->get_screen_light_level() << endl;
	}
	cout << endl;
	system("pause");
	XuatThongTinCaiDat();
}

// ---- Xuất tất cả thông tin cài đặt -------
void XuatThongTatCaTinCaiDat() {

	cout << " " << left
		<< setw(20) << "Owner name"
		<< setw(30) << "Email"
		<< setw(15) << "Key number"
		<< setw(15) << "ODO number"
		<< setw(22) << "Remind service (km)"
		<< setw(8) << "Light"
		<< setw(15) << "Screen light"
		<< setw(13) << "Taplo light"
		<< setw(8) << "Media"
		<< setw(8) << "Call"
		<< setw(13) << "Navigation"
		<< setw(15) << "Notification"
		<< setw(15) << "Timezone"
		<< setw(10) << "Language" << endl;

	for (int i = 0; i < carCount; ++i) {
		Setting* common = display.get(i);
		Display* displayLevels = static_cast<Display*>(display.get(i));
		Sound* soundLevels = static_cast<Sound*>(sound.get(i));
		General* generalSettings = static_cast<General*>(general.get(i));

		cout << " " << left
			<< setw(20) << common->getOwnerName()
			<< setw(30) << common->getEmail()
			<< setw(15) << common->getPersonalKey()
			<< setw(15) << common->getODO()
			<< setw(22) << common->getServiceRemind()
			<< setw(8) << displayLevels->get_light_level()
			<< setw(15) << displayLevels->get_screen_light_level()
			<< setw(13) << displayLevels->get_taplo_light_level()
			<< setw(8) << soundLevels->get_media_level()
			<< setw(8) << soundLevels->get_call_level()
			<< setw(13) << soundLevels->get_navi_level()
			<< setw(15) << soundLevels->get_notification_level()
			<< setw(15) << rutGonTimeZone(generalSettings->get_timeZone())
			<< setw(10) << generalSettings->get_language()
			<< endl;
	}
	cout << endl;
	system("pause");
	XuatThongTinCaiDat();
}


//=============== Một vài hàm hỗ trợ ==============================
int searchKey(const List<Setting*>& arr, int num, const string& str)
{
	for (int i = 0; i < num; i++)
	{
		if (str == arr.get(i)->getPersonalKey())
		{
			return i;
		}
	}
	return -1;
}

// -------- copy thông tin chung từ các object con -----------
void copySettingInfo(Setting* info1, Setting* info2, Setting* info3)
{
	info2->setOwnerName(info1->getOwnerName());
	info2->setEmail(info1->getEmail());
	info2->setPersonalKey(info1->getPersonalKey());
	info2->setODO(info1->getODO());
	info2->setServiceRemind(info1->getServiceRemind());

	info3->setOwnerName(info1->getOwnerName());
	info3->setEmail(info1->getEmail());
	info3->setPersonalKey(info1->getPersonalKey());
	info3->setODO(info1->getODO());
	info3->setServiceRemind(info1->getServiceRemind());

}

// rút gọn Timezone, chỉ lấy phần bên trong ()
string rutGonTimeZone(const string& str)
{
	size_t start = str.find('(');
	size_t end = str.find(')');

	// Trích xuất và in ra phần giữa dấu '(' và ')'
	if (start != string::npos && end != string::npos && end > start) {
		return str.substr(start + 1, end - start - 1);
	}

	return "N/A";
}

//rút gọn language, lấy phần phía sau "/"
string rutGonLanguage(const string& str)
{
	size_t start = str.find('/');

	if (start != string::npos) {
		return str.substr(start + 2);
	}

	return "";
}

//============== Các hàm liên quan đến FILE =========================
//----------copy dữ liệu từ các settings vào file settings.txt-------
void uploadSettings()
{
	ofstream f("settings.txt");
	if (f.fail())
	{
		cout << " Khong mo duoc file settings.txt" << endl;
		return;
	}

	for (int i = 0; i < carCount; ++i) {
		Setting* common = display.get(i);
		Display* displayLevels = static_cast<Display*>(display.get(i));
		Sound* soundLevels = static_cast<Sound*>(sound.get(i));
		General* generalSettings = static_cast<General*>(general.get(i));

		f << "Common: [" << common->getOwnerName() << "]["
			<< common->getEmail() << "]["
			<< common->getPersonalKey() << "]["
			<< common->getODO() << "]["
			<< common->getServiceRemind() << "]"
			<< " Display: " << "[" << displayLevels->get_light_level() << "]["
			<< displayLevels->get_screen_light_level() << "]["
			<< displayLevels->get_taplo_light_level() << "]"
			<< " Sound: " << "[" << soundLevels->get_media_level() << "]["
			<< soundLevels->get_call_level() << "]["
			<< soundLevels->get_navi_level() << "]["
			<< soundLevels->get_notification_level() << "]"
			<< " General: " << "[" << generalSettings->get_timeZone() << "]["
			<< generalSettings->get_language() << "]"
			<< endl;
	}

	f.close();
}
//----------lấy dữ liệu từ file settings.txt để copy vào các list---------
void downloadSettings()
{
	ifstream f("settings.txt");
	if (f.fail())
	{
		cout << " Khong mo duoc file settings.txt" << endl;
		return;
	}
	int i = 0;
	string line;

	while (getline(f, line))
	{
		int i = 0;
		regex pattern(R"(\[([^\]]+)\])");
		smatch match;
		vector<string> results;
		auto it = line.cbegin();
		while (regex_search(it, line.cend(), match, pattern))
		{
			results.push_back(match[1]);
			it = match.suffix().first;
		}

		if (results.size() < 14) {
			cout << "Dòng " << i + 1 << " thiếu dữ liệu. Bỏ qua.\n";
			continue;
		}

		if (
			!isValidUnsignedInt2(results[3]) ||  // ODO
			!isValidUnsignedInt2(results[4]) ||  // ServiceRemind
			!isValidUnsignedInt2(results[5]) ||  // Display: light_level
			!isValidUnsignedInt2(results[6]) ||  // screen_light_level
			!isValidUnsignedInt2(results[7]) ||  // taplo_light_level
			!isValidUnsignedInt2(results[8]) ||  // Sound: media_level
			!isValidUnsignedInt2(results[9]) ||  // call_level
			!isValidUnsignedInt2(results[10]) || // navi_level
			!isValidUnsignedInt2(results[11])    // notification_level
			)
		{
			cout << "Dòng " << i + 1 << " chứa dữ liệu không hợp lệ. Bỏ qua.\n";
			continue;
		}

		Setting* sD = new Display();
		Setting* sS = new Sound();
		Setting* sG = new General();


		sD->setOwnerName(results[0]);
		sD->setEmail(results[1]);
		sD->setPersonalKey(results[2]);
		sD->setODO(stoi(results[3]));
		sD->setServiceRemind(stoi(results[4]));

		copySettingInfo(sD, sS, sG); // copy thông tin chung cho nhau

		//cài đặt riêng thì ép kiểu sang từng lớp con để gọi hàm
		static_cast<Display*>(sD)->set_light_level(stoi(results[5]));
		static_cast<Display*>(sD)->set_screen_light_level(stoi(results[6]));
		static_cast<Display*>(sD)->set_taplo_light_level(stoi(results[7]));

		static_cast<Sound*>(sS)->set_media_level(stoi(results[8]));
		static_cast<Sound*>(sS)->set_call_level(stoi(results[9]));
		static_cast<Sound*>(sS)->set_navi_level(stoi(results[10]));
		static_cast<Sound*>(sS)->set_notification_level(stoi(results[11]));

		static_cast<General*>(sG)->set_timeZone(results[12]);
		static_cast<General*>(sG)->set_language(results[13]);

		display.add(sD, carCount);
		sound.add(sS, carCount);
		general.add(sG, carCount);
		carCount++;
		i++;
	}

	f.close();
}

//---------------Download timezone từ file vào vector ------
void downloadTimeZone()
{
	ifstream f("timezones.txt");
	if (f.fail())
	{
		ofstream f1("timezones.txt");
		if (f1.fail())
		{
			cout << " Khong mo duoc file timezones.txt" << endl;
			return;
		}

		//Nếu không mở được file, tạo ra một danh sách và lưu vào một file mói
		f1 << "(GMT-12:00) / International Date Line West\n";
		f1 << "(GMT-11:00) / Midway Island, Samoa\n";
		f1 << "(GMT-10:00) / Hawaii\n";
		f1 << "(GMT-09:00) / Alaska\n";
		f1 << "(GMT-08:00) / Tijuana, Baja California\n";
		f1 << "(GMT-07:00) / Chihuahua, La Paz, Mazatlan - New\n";
		f1 << "(GMT-06:00) / Guadalajara, Mexico City, Monterrey - New\n";
		f1 << "(GMT-05:00) / Eastern Time(US and Canada)\n";
		f1 << "(GMT-04:00) / Atlantic Time(Canada)\n";
		f1 << "(GMT-03:30) / Newfoundland\n";
		f1 << "(GMT-02:00) / Mid-Atlantic\n";
		f1 << "(GMT-01:00) / Azores\n";
		f1 << "(GMT+00:00) / Monrovia, Reykjavik\n";
		f1 << "(GMT+01:00) / Belgrade, Bratislava, Budapest, Ljubljana, Prague\n";
		f1 << "(GMT+02:00) / Minsk\n";
		f1 << "(GMT+03:00) / Moscow, St.Petersburg, Volgograd\n";
		f1 << "(GMT+04:00) / Abu Dhabi, Muscat\n";
		f1 << "(GMT+04:30) / Kabul\n";
		f1 << "(GMT+05:00) / Tashkent\n";
		f1 << "(GMT+05:30) / Chennai, Kolkata, Mumbai, New Delhi\n";
		f1 << "(GMT+05:45) / Kathmandu\n";
		f1 << "(GMT+06:00) / Astana, Dhaka\n";
		f1 << "(GMT+06:30) / Yangon(Rangoon)\n";
		f1 << "(GMT+07:00) / Bangkok, Hanoi, Jakarta\n";
		f1 << "(GMT+08:00) / Beijing, Chongqing, Hong Kong, Urumqi\n";
		f1 << "(GMT+08:00) / Irkutsk, Ulaanbaatar\n";
		f1 << "(GMT+09:00) / Seoul\n";
		f1 << "(GMT+09:30) / Adelaide\n";
		f1 << "(GMT+10:00) / Canberra, Melbourne, Sydney\n";
		f1 << "(GMT+11:00) / Magadan, Solomon Islands, New Caledonia\n";
		f1 << "(GMT+12:00) / Fiji, Kamchatka, Marshall Is.\n";
		f1 << "(GMT+13:00) / Nuku'alofa\n";

		f1.close();
		f.open("timezones.txt");
	}

	//đọc file và lưu vào vector 
	string line;
	int index = 1;
	while (getline(f, line)) {
		CommonInfo tz;
		tz.setNumber(to_string(index));
		tz.setName(line);

		timezoneList.push_back(tz);
		index++;
	}

	f.close();

}


//---------------tương tự là việc lấy dữ liệu từ file languages.txt
void downloadLanguage() {




	ifstream f("languages.txt");
	if (f.fail())
	{
		ofstream f1("languages.txt");
		if (f1.fail())
		{
			cout << " Khong mo duoc file languages.txt" << endl;
			return;
		}

		f1 << "1 / Mandarin (entire branch)\n";
		f1 << "2 / Spanish\n";
		f1 << "3 / English\n";
		f1 << "4 / Hindi\n";
		f1 << "5 / Arabic\n";
		f1 << "6 / Portuguese\n";
		f1 << "7 / Bengali\n";
		f1 << "8 / Russian\n";
		f1 << "9 / Japanese\n";
		f1 << "10 / Punjabi\n";
		f1 << "11 / German\n";
		f1 << "12 / Javanese\n";
		f1 << "13 / Wu(inc.Shanghainese)\n";
		f1 << "14 / Malay(inc.Indonesian and Malaysian)\n";
		f1 << "15 / Telugu\n";
		f1 << "16 / Vietnamese\n";
		f1 << "17 / Korean\n";
		f1 << "18 / French\n";
		f1 << "19 / Marathi\n";
		f1 << "20 / Tamil\n";
		f1 << "21 / Urdu\n";
		f1 << "22 / Turkish\n";
		f1 << "23 / Italian\n";
		f1 << "24 / Yue(inc.Cantonese)\n";
		f1 << "25 / Thai\n";
		f1 << "26 / Gujarati\n";
		f1 << "27 / Jin\n";
		f1 << "28 / Southern Min\n";
		f1 << "29 / Persian\n";
		f1 << "30 / Polish\n";

		f1.close();
		f.open("languages.txt");
	}

	string line;
	int index = 1;
	while (getline(f, line))
	{
		CommonInfo lang;
		lang.setNumber(to_string(index));
		lang.setName(rutGonLanguage(line));

		languageList.push_back(lang);
		index++;
	}

	f.close();
}

//------sắp xếp các thành viên trong list theo personal key, bubble sort------
void sapXep(List<Setting*>& listArr)
{
	for (int i = 0;i < carCount - 1; i++)
	{
		int swapCount = 0;
		for (int j = 0; j < carCount - 1 - i; j++)
		{
			if (stoi(listArr.get(j)->getPersonalKey()) > stoi(listArr.get(j + 1)->getPersonalKey()))
			{
				listArr.Sap_Xep(j, j + 1);
				swapCount++;
			}
		}

		if (swapCount == 0)
			break;
	}

}


