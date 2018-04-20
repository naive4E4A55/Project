#pragma once
//这是一个比较差的模板,升级版在Group.h中
#include<vector>
#include"Order.h"
#include "OrderGroup.h"
#include <map>
using namespace std;
//模板类,类的实现必须在.h文件里
template<class ClassificationData> //分类数据
class OrderSet		//有个ClassificationData的标签,用于代表这一个集合的代表元素
{
private:
	ClassificationData representativeElement;//分类标准变量
	vector<Order*> pOrderGroup;				  //分类后的订单集合,用"引用",这样用着舒服
	map<ClassificationData, Order>orderMap;   //订单map,用于方便查重,ClassificationData是关键词,可能是string可能是time可能是address
	//int number;
public:
	OrderSet() {};
	~OrderSet() {};
	ClassificationData get_representative_element() { return representativeElement; }
	//OrderSet(OrderGroup& nOrderGroup);//设置OrderSet
	void set_representativeElement(ClassificationData nRepresentativeElement) { representativeElement = nRepresentativeElement; pOrderGroup.clear(); orderMap.clear(); }
	void add_order(ClassificationData representativeElement,Order nOrder);//设置OrderSet
	bool exist_set(ClassificationData& representativeElement);//这个order存在于set里
	int get_size() { return pOrderGroup.size(); }
};

template<class ClassificationData> //分类数据
void OrderSet<ClassificationData>::add_order(ClassificationData representativeElement,Order nOrder)
{
	if (!exist_set(representativeElement))
	{
		//orderMap.insert(map<Order, string>::value_type(nOrder, nOrder.get_ID()));
		orderMap.insert(map<ClassificationData, Order>::value_type(representativeElement,nOrder));
		pOrderGroup.push_back(&nOrder);
	}
}
template<class ClassificationData> //分类数据
bool OrderSet<ClassificationData> ::exist_set(ClassificationData& representativeElement)//这个order存在于set里
{
	return orderMap.count(representativeElement);
}
;