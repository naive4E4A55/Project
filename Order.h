#pragma once
#include <string>
#include "OrderTime.h"
#include "ChildNote.h"
#include "Note.h"
#include "Phone.h"
#include "Address.h"
#include "WpName.h"
#include <fstream>
//typedef string WpName;
using namespace std;
class Order
{
#define make_get_func(type,name)\
		type _CONCAT(get_,name)()const{ return name;}//预处理宏,生成get group函数
#define do_clear5(name1,name2,name3,name4,name5)\
		_CONCAT(name1,.clear();)\
		_CONCAT(name2,.clear();)\
		_CONCAT(name3,.clear();)\
		_CONCAT(name4,.clear();)\
		_CONCAT(name5,.clear();)//预处理宏,用于简化clear类型
private:
	bool change;
	string ID;
	string orderID;
	WpName name;//订单名称
	OrderTime orderTime;
	string seller;
	double orderPrice;
	Note note;
	int status;
	string userName;
	Phone phone;
	Address address;
	string userID;
	OrderTime createrTime;
	int type;
	string userFlag;
	string cpName;
	string mailno;
	int tagFlag;
	//获取","分割的内容
	string get_child(string& str,char c);
	string get_string(string::iterator p, string::iterator end)const;
	string get_note_string(string& str);//专门获取note所需的内容
	template <class Type>
	Type stringToNum(const string& str);
public:
	Order();
	~Order();
	void clear();
	// 初始化订单
	void set_order(string str);
	void operator=(Order& nOrder);
	bool operator<(Order& nOrder) { return ID < nOrder.ID; }
	bool operator>(Order& nOrder) { return ID > nOrder.ID; };
	void operator<<(string str) { set_order(str); }
	bool operator==(Order& nOrder)const { return (ID == nOrder.ID) && (1/*orderID == nOrder.orderID*/); }
	//bool operator==(const Order& nOrder)const { return (ID == nOrder.ID) && (orderID == nOrder.orderID); }
	friend bool operator==(const Order& order1, const Order& order2);
	friend bool operator==(const Order& order1, Order& order2);
	friend bool operator<(const Order& order1, const Order& order2);
	friend bool operator>(const Order& order1, const Order& order2);
	friend fstream& operator<<(fstream& outFile, Order& order);
	friend ostream& operator<<(ostream& outFile, Order& order);
	make_get_func(string, ID);
	make_get_func(string, orderID);
	make_get_func(WpName,name);
	make_get_func(OrderTime,orderTime);
	make_get_func(string, seller);
	make_get_func(double, orderPrice);
	make_get_func(Note, note);
	make_get_func(int, status);
	make_get_func(string, userName);
	make_get_func(Phone, phone);
	make_get_func(Address, address);
	make_get_func(string, userID);
	make_get_func(OrderTime, createrTime);
	make_get_func(int, type);
	make_get_func(string, userFlag);
	make_get_func(string, cpName);
	make_get_func(string, mailno);
	make_get_func(int, tagFlag);
};
static fstream& operator<<(fstream& outFile, Order& order)
{
	//输出order的信息
	outFile << order.ID << ",";
	outFile << order.seller << ",";
	outFile << order.name<<",";
	outFile << order.userName << ",";
	outFile << order.phone << ",";
	outFile << order.address << ",";
	outFile << order.orderTime << ",";
	outFile << order.note << ",";
	outFile << order.status << ",";
	return outFile;
}

static ostream& operator<<(ostream& outFile, Order& order)
{
	//输出order的信息
	outFile << order.ID << ",";
	outFile << order.seller << ",";
	outFile << order.name << ",";
	outFile << order.userName << ",";
	outFile << order.phone << ",";
	outFile << order.address << ",";
	outFile << order.orderTime << ",";
	outFile << order.note << ",";
	outFile << order.status << ",";
	return outFile;
}
;

;