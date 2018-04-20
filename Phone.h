#pragma once
#include <string>
#include <fstream>
using namespace std;
class Phone
{
private:
	string phoneNumber;
public:
	Phone();
	~Phone();
	void clear() { phoneNumber.shrink_to_fit(); }
	void set_number(string number);	// 获取手机号
	void operator=(Phone nPhone) { phoneNumber = nPhone.phoneNumber; }
	void operator<<(string number) { set_number(number); }
	int operator==(string number) { return phoneNumber == number; }
	int operator!=(string number) { return !(phoneNumber == number); }
	string get_number()const { return phoneNumber; }
	bool operator ==(Phone& nPhone)const { return nPhone.get_number() == phoneNumber; }
	bool operator !=(Phone& nPhone)const { return !(*this == nPhone); }
	friend fstream& operator<<(fstream& outFile, Phone& phone);
	friend ostream& operator<<(ostream& outFile, Phone& phone);
};
static fstream& operator<<(fstream& outFile, Phone& phone)
{
	outFile << phone.phoneNumber;
	return outFile;
}

static ostream& operator<<(ostream& outFile, Phone& phone)
{
	outFile << phone.phoneNumber;
	return outFile;
}


;