#pragma once
//这是一个模板
#include<vector>
#include <map>
#include <algorithm>//添加STL模板算法
#include <iostream>
using namespace std;
//模板类,类的实现必须在.h文件里
//这个类似于map
/**************
解释一下这个的用法:
这个是一个类似于map的模板,作用是:把一组关键词相同的数据给合并到一起
分别有三个参数:
			第一个参数:这一组数据的关键词(这些数据的关键词都相同)
			第二个参数:每个数据的特征值(Name),就是这个数据区别于其他数据的元素
			第三个参数:数据本身
例如,我想弄一个,购买者为"A"的订单的集合,那么就应该让这一组数据的关键词为A
										Name为这些订单的ID(订单的ID是独一无二的,用以区分)
										Data为订单本身
如果关键词A为string类型,ID也是string类型,那么就应该实例化为:Group<string,string,Order> orderGroupByUserName;
**************/
template<class KeyWord,class Name,class Data> //分类数据
class Group
{
private:
	KeyWord keyWord;
	vector<Data*> dataGroup;
	map<Name,Data> dataMap;//防止重复的加入,用一个树来存储
public:
	Group() {};
	Group(KeyWord nKeyWord) { clear(); keyWord = nKeyWord; }
	~Group() { clear(); };
	void clear(); 

	//set_keyword会清空已有的所有数据
	void set_keyWord(KeyWord nKeyWord) { clear(); keyWord = nKeyWord; }

	KeyWord get_keyWord() { return keyWord; }

	//这两个函数,返回的都是Data的引用
	Data& find_data(int i) { if (i >= (int)dataGroup.size())throw"haven't"; return *dataGroup[i]; }
	Data& find_data(Name nName);

	//Name get_name(int i) { if (i >= (int)dataGroup.size())throw"haven't"; return dataGroup[i]}
	void add_data(KeyWord nKeyWord,Name nName,Data nData);

	//void add_childData();
	bool exist_group(Name nName) { return dataMap.count(nName); };

	unsigned int get_size() { return (unsigned int)dataGroup.size(); }

	//要重载一下[]运算符

	//排序函数,不可避免地使用指针,因为有一个vector<Order*>的定义
	void sort_by_function(int(*fcmp)(Data* pData1, Data* pData2));

	//输出两个Data的相似度的函数
	double sml_num(unsigned int i, unsigned int j);// { return (*Data[i]).sml_num((*Data[j])); }
	double sml_num(Name name1, Name name2) { return find_data(name1).sml_num(find_data(name2)); }


};

template<class KeyWord,class Name ,class Data>
void Group<KeyWord,Name,Data>::add_data(KeyWord nKeyWord,Name nName,Data nData)
{
	//cout << nKeyWord << endl;
	if (nKeyWord != keyWord) return;
	if (!exist_group(nName))
	{
		//dataMap.insert(map<Name, Data>::value_type(nName,nData));
		dataMap.insert(map<Name, Data>::value_type(nName,nData));
		if(exist_group(nName))
			dataGroup.push_back(&find_data(nName));
		else;
	}
}

template<class KeyWord, class Name, class Data>
void Group<KeyWord, Name, Data>::clear()
{
	for (unsigned int i = 0; i < dataGroup.size(); i++)
		(*dataGroup[i]).clear();
	//dataGroup.clear(); dataMap.clear();
	//dataGroup.swap(dataGroup);
	//dataMap.swap(dataMap);
	dataGroup.swap(vector<Data*>()); dataMap.swap(map<Name, Data>());
}

template<class KeyWord, class Name, class Data>
Data& Group<KeyWord, Name, Data>::find_data(Name nName)
{
	//map<Name, Data>::iterator it;
	//it = dataMap.find(nName);
	//if (res==dataMap.end())
	//	throw"haven't";//如果找不到,就返回尾部指针,抛出"haven't"
	//return *res;
	//for(unsigned int i=0;i<)
	/*for(unsigned int i=0;i<dataGroup.size();i++)
		if(dataGroup[i])*/
	//throw 'a';
	/*map<Name, Data*>::iterator it = dataMap.find(nName);
	if(it==dataMap.end())
		throw"haven't";//如果找不到,就返回尾部指针,抛出"haven't"
	else
	{
		return //*it.secend;
	}*/
	if (dataMap.count(nName))
	{
		return dataMap[nName];
	}
	else throw"haven't";//如果找不到,就抛出"haven't"
}

template<class KeyWord, class Name, class Data>
void Group<KeyWord, Name, Data>::sort_by_function(int(*fcmp)(Data* pData1, Data* pData2))
{
	//sort(dataGroup)
	sort(dataGroup.begin(), dataGroup.end(), fcmp);
}



//很丑的一个函数,计算两个相似度
template<class KeyWord, class Name, class Data>
double Group<KeyWord, Name, Data>::sml_num(unsigned int i, unsigned int j)
{
	
}


;