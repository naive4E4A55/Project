#pragma once
#include <string>
#include <vector>
#include <map>
#include <algorithm>//添加STL模板算法
#include <cmath>
#include "ChildNote.h"
using namespace std;
class Note
{
#define smlAverage 0.5
private:
	vector<ChildNote> note;
	double inner_product(vector<double> vec1, vector<double>vec2);
	double model(vector<double> vec);
	double degress(vector<double> vec1, vector<double> vec2);
	string get_string(string::iterator begin, string::iterator end);
public:
	Note();
	~Note();
	string max_same_string(const string& str1, const string& str2);
	void set_note(string str);
	bool exist_name(string& name);
	inline ChildNote find_by_name(string& name);
	void sort_note();//把ChileMote按名字的升序排列
	void operator=(Note& nNote) { for (unsigned int i = 0; i < nNote.note.size(); i++) note.push_back(nNote.note[i]); }
	void operator<<(string str) { set_note(str); }
	friend fstream& operator<<(fstream& outFile, Note& note);
	friend ostream& operator<<(ostream& outFile, Note& note);

	ChildNote get_child_note(int i)const { if (i >= (int)note.size()) throw "haven't ChileNote[i]"; else return note[i]; };
	int size()const { return (int)note.size(); }

	void clear();
	//需要补齐的重要函数
	//体现两个note的相似度
	double sml_num(Note nNote);
	//课程订单,先不支付,联系客服
	//走出学习误区单词篇
};
static fstream& operator<<(fstream& outFile, Note& note)
{
	if (note.size() != 0)
	{
		outFile << "\"[";
		for (unsigned int i = 0; i < note.note.size() - 1; i++)
		{
			outFile << note.note[i] << ",";
		}
		outFile << note.note[note.note.size() - 1] << "]\"";
	}
	else outFile << "[]";
	return outFile;
}

static ostream& operator<<(ostream& outFile, Note& note)
{
	if (note.size() != 0)
	{
		outFile << "\"[";
		for (unsigned int i = 0; i < note.note.size() - 1; i++)
		{
			outFile << note.note[i] << ",";
		}
		outFile << note.note[note.note.size() - 1] << "]\"";
	}
	else outFile << "[]";
	return outFile;
}


;