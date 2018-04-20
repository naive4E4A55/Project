#include "Order.h"
#include <sstream>    //使用stringstream需要引入这个头文件 
#include <iostream>
using namespace std;

/*将字符串转为任意类型数据的模板*/
template <class Type>
Type Order::stringToNum(const string& str)
{
	if (str.size() == 0)
		return 0;
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
/***********模板结束*************/


Order::Order()
{
	orderPrice = 0.0;
	status = 0;
	type = 0;
	tagFlag = 0;
	change = 0;
}


Order::~Order()
{
	clear();
}

void Order::clear()
{
	orderPrice = 0.0;
	status = 0;
	type = 0;
	tagFlag = 0;
	change = 0;
	ID=""; orderID=""; name.shrink_to_fit(); orderTime.clear(); seller="";
	note.clear(); userName=""; phone.clear(); address.clear(); userID="";
	createrTime.clear(); userFlag=""; cpName=""; mailno="";
	/*ID.swap(ID); orderID.swap(orderID); name.swap(name); orderTime.clear(); seller.swap(seller);
	note.clear(); userName.swap(userName); phone.clear(); address.clear(); userID.clear();
	createrTime.clear(); userFlag.swap(userFlag); cpName.swap(cpName); mailno.swap(mailno);*/
	//do_clear5(ID, orderID, name,orderTime,seller);
	//do_clear5(note, userName, phone, address, userID);	//写到这里的时候做了什么操作,鼠标点哪里代码就跟到哪里
	//do_clear5(createrTime, userFlag, cpName, mailno, mailno);//五杀不够,mailno来凑;强行凑5个用宏
	/*ID.clear();
	orderID.clear();
	name.clear();
	orderTime.clear();
	seller.clear();*/
	/*note.clear();
	userName.clear();
	phone.clear();
	address.clear();
	userID.clear();*/
	/*createrTime.clear();
	userFlag.clear();
	cpName.clear();
	mailno.clear();*/
}


//获取从p0到end的字符串
string Order::get_string(string::iterator p, string::iterator end)const
{
	string s;
	for (; p != end; p++)
	{
		if (*p == '\0') { cout <<"问题字符串为:"<<endl<<s << endl; throw'b'; }
		s += *p;
	}
	return s;
}


//获取用字符"c"分割的内容,同时把"当作转义字符,也就是说如果是","的形式,就不会用这个","进行分隔
string Order::get_child(string& str,char c)
{
	string s;
	string::iterator p=str.begin();
	int number = 0;
	//获取从*p到第一个","的内容
	for (; *p != c||number%2==1; p++)
	{
		s += *p;
		if (*p == '\"')number++;
	}
	p++;
	str = get_string(p,str.end());
	return s;
}

string Order::get_note_string(string& str)//专门获取note所需的内容
{
	string::iterator p = str.begin();
	string s;
	int number = 0;
	while ((p!=str.end())&&!(number == 0 && *p == ','))
	{
		if (*p == '\0')throw 'c';
		s += *p;
		if (*p == '[')number++;
		if (*p == ']')number--;
		p++;
	}
	if (p == str.end())throw 4;
	p++;
	if (p == str.end())throw 5;
	str = get_string(p,str.end());
	return s;
}


// 初始化订单
void Order::set_order(string str)
{
	ID = get_child(str,',');
	orderID = get_child(str,',');
	name = get_child(str,',');
	string s = get_child(str,',');
	orderTime.set_time(s);s.clear();
	seller = get_child(str,',');
	s = get_child(str,',');
	orderPrice = stringToNum<double>(s); s.clear();
	s = get_note_string(str);
	note.set_note(s); s.clear();
	s = get_child(str,',');
	status = stringToNum<int>(s); s.clear();
	userName = get_child(str,',');
	phone.set_number(get_child(str,','));
	address.set_address(get_child(str,','));
	userID = get_child(str,',');
	createrTime.set_time(get_child(str,','));
	type = stringToNum<int>(get_child(str,','));
	userFlag = get_child(str,',');
	cpName = get_child(str,',');
	mailno = get_child(str,',');
	tagFlag = stringToNum<int>(str);
	/*string ID;
	string orderID;
	string name;
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
	int tagFlag;*/
}

void Order::operator=(Order& nOrder)
{
	ID = nOrder.ID;
	orderID = nOrder.orderID;
	name = nOrder.name;
	orderTime = nOrder.orderTime;
	seller = nOrder.seller;
	orderPrice = nOrder.orderPrice;
	note = nOrder.note;
	status = nOrder.status;
	userName = nOrder.userName;
	phone = nOrder.phone;
	address = nOrder.address;
	userID = nOrder.userID;
	createrTime = nOrder.createrTime;
	type = nOrder.type;
	userFlag = nOrder.userFlag;
	cpName = nOrder.cpName;
	mailno = nOrder.mailno;
	tagFlag = nOrder.tagFlag;
}
bool operator==(const Order& order1, const Order& order2)
{
	return (order1.ID == order2.ID) && (1/*order1.orderID == order2.orderID*/);
}
bool operator==(const Order& order1, Order& order2)
{
	return (order1.ID == order2.ID) && (1/*order1.orderID == order2.orderID*/);
}
bool operator<(const Order& order1, const Order& order2)
{
	return order1.ID < order2.ID;
}
bool operator>(const Order& order1, const Order& order2)
{
	return order1.ID > order2.ID;
}

//fstream& operator<<(fstream& outFile, const Order& order)
//{
//	
//}