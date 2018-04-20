#pragma once
#include "Order.h"
#include <vector>
#include <deque>
#include <list>
#include <map>
#define filtration
//#include <fstream>
//进行订单的分析与整合推荐使用map进行防止订单重复
using namespace std;
class OrderGroup
{
private:
	vector<Order> orderGroup;//订单集合 感觉这个用deque好像也可以,但是没什么必要,deque能做到快速在首尾增删元素
	list<Order>orderList;//orderList,用于初始化队列
	//反了,反了,反了!但是没出错... 应该是map<string ,Order>
	map<string,Order>orderMap;//用order.ID作为特征值orderMap
	string delete_char(string sNewTag,char cRddcy);	//去除掉一行中的某些字符
	void delete_child_string(string& str,char c);
	string get_string(string::iterator p, string::iterator end)const;
	string get_child(string& str, char c);
	bool exist_string(const string& str1, const string& str2);
	void list_to_vector();
	bool exist_list(string& str)const;
public:
	OrderGroup();
	~OrderGroup();
	void clear();
	bool order_right(const Order& nOrder);
	bool exist_group(Order& order)const;//判断一个order是否处于这个集合中
	//进行订单统计及整合
	//读取文件,进行分析
	int set_group(string fileName);
	unsigned int get_size() { return (unsigned int)orderGroup.size(); }
	Order get_order(int i);//获取某个order
	vector<Order> get_order_by_userName(string userName);//通过用户姓名获得某群order
};

