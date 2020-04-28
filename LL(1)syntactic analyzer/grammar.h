#pragma once
#include<iostream>
#include<vector>
#include<map>
using namespace std;
class Grammar
{
protected:	
	vector<string> vg;      //产生式
	map<char, int> mv;     //非终结符和终结符键值对
	string grammar[10];     //文法
	string first[100];      //first集
	string follow[100];     //follow集
	char vn[10];            //非终结符号
	char vt[10];            //终结符号
	int num;                //文法条数
	int numvn;              //非终结符号数
	int numvt;              //终结符号数
	int table[100][100];    //产生式表
	string sentence;        //句子
public:
	Grammar();
	void init();
	void remove_leftrecursion();
	void remove_leftcommon_factor();
	void getfirst();
	void getfollow();
	void gettable();
	bool if_vn(char);
	bool if_vt(char);
	bool if_LL1();
	string get_f(int i,int k,bool &empty);
	void analyze();
};
Grammar::Grammar()
{
	num = 0;
	numvt = 0;
	numvn = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
			table[i][j] = 100;
	}
}
