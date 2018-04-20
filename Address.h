#pragma once
#include <string>
#include <fstream>
using namespace std;
class Address
{
	int type;//类型,0代表是省市区分类,1代表电话号分类
	string province;//省
	string city;	//市
	string county;	//区/县
	string town;	//镇
	string other;	//其他信息
	string get_child_address(string& str);
	string get_child_number(string& str);
	string get_string(string::iterator begin, string::iterator end);
public:
	Address();
	~Address();
	void clear() { type = 0; province.shrink_to_fit(); city.shrink_to_fit(); county.shrink_to_fit(); town.shrink_to_fit(); other.shrink_to_fit(); }//province.swap(province); city.swap(city); county.swap(county); town.swap(town); other.swap(other); }
	void set_address(string str);
	void operator=(Address& nAddress) { type = nAddress.type; province = nAddress.province; city = nAddress.city; county = nAddress.county; town = nAddress.town; other = nAddress.other;}
	void operator<<(string str) { set_address(str); }
	friend fstream& operator<<(fstream& outFile, Address& address);
	friend ostream& operator<<(ostream& outFile, Address& address);
	int get_type() { return type; }
	string get_province() { return province; }
	string get_city() { return city; }
	string get_town() { return town; }
	string get_county() { return county; }
	string get_other() { return other; }
	string get_all() { return province + city + county + town + other; }
};

static fstream& operator<<(fstream& outFile, Address& address)
{
	outFile << address.province << "\t" << address.city << "\t" << address.county << "\t" << address.town << address.other;
	return outFile;
}

static ostream& operator<<(ostream& outFile, Address& address)
{
	outFile << address.province << "\t" << address.city << "\t" << address.county << "\t" << address.town << address.other;
	return outFile;
}

;
