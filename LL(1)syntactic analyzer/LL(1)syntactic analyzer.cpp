// LL(1)syntactic analyzer.cpp: 定义控制台应用程序的入口点。
//

#include"grammar.h"
#include<string>
#include<iostream>
#include<vector>
#include<set>
#include<stack>
#include<iomanip>
#include<time.h>
using namespace std;

//string grammar[10];           //文法
//string first[100];           //first集
//string follow[100];          //follow集
//char vt[10];                 //终结符
//char vn[10];                 //非终结符

void remove_dup(string &a, string b)      //去重复元素
{
	set<char> s;
	set<char>::iterator it;
	for (int i = 0; i < a.size(); i++)
	{
		s.insert(a[i]);
	}
	for (int i = 0; i < b.size(); i++)
	{
		s.insert(b[i]);
	}
	a.clear();
	for (it = s.begin(); it != s.end(); it++)
	{
		a = a + *it;
	}
}

void prefix_match(string s1, string s2, vector<string> &vg, int i, int j)
{
	/*if (s1[0] == s2[0] && s1[1] == s2[1] && s1.size() > 2 && s2.size() > 2)
	{
		bool b = 1;
		while(b)
		{
			srand(time(0));
			char c = rand() % 26 + 'A';      //随机产生一个大写字母
			if(this->if_vt(c))
		}
	}*/
}

bool intersection(string a, string b)
{
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			if (a[i] == b[j])
				return 1;
		}
	}
	return 0;
}

string Grammar::get_f(int i, int k, bool &empty)    //推出vg[i][k]能推导出的所有不含空的vn集合，并且判断vg[i][k]能否推出空
{
	string s;
	if (vg[i][k] == '$')     //如果是空，则空标记记1
	{
		empty = 1;
	}
	else if (if_vt(vg[i][k]))     //如果是终结符，则返回这个终结符
	{
		s = vg[i][k];
		return s;
	}
	for (int j = 0; j < vg.size(); j++)
	{
		if (vg[j][0] == vg[i][k])
		{
			s = s + get_f(j, 1, empty);
		}
	}
	//cout << s << endl;
	return s;
}

bool Grammar::if_vn(char c)     //判定非终结符
{
	for (int i = 0; i < numvn; i++)
	{
		if (c == vn[i])
			return 1;
	}
	return 0;
}

bool Grammar::if_vt(char c)       //判定终结符
{
	for (int i = 0; i < numvt; i++)
	{
		if (c == vt[i])
			return 1;
	}
	return 0;
}

//First集中含有ε的非终结符的Follow集与其First集交集是否为空
bool Grammar::if_LL1()
{
	for (int i = 0; i < numvn; i++)      //遍历非终结符
	{
		bool b = 0;
		for (int j = 0; j < first[mv[numvn + 1 + i]].size(); j++)     //遍历非终结符的first
		{
			if (first[mv[numvn + 1 + i]][j] == '$')
			{
				if (intersection(first[mv[numvn + 1 + i]], follow[mv[numvn + 1 + i]]))
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

void Grammar::init()
{
	int i = 0,j = 0;
	char c;
	cout << "输入文法条数:";
	cin >> num;
	cout << "输入所有终结符:";
	mv['#'] = 0;       //设定'#'为0
	vt[0] = '#';
	numvt++;
	while ((c = getchar()) != '@')         //输入到*结束输入
	{
		if (c >= 33 && c <= 127)
		{
			numvt++;
			vt[i + 1] = c;
			i++;
			mv[c]=i;
		}
	}
	i++;
	mv['$'] = i;      //空
	vt[i] = '$';
	//cout << numvt << endl;
	//cout << mv['Q'];
	cout << "输入所有非终结符:";
	while ((c = getchar()) != '@')
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			numvn++;
			vn[j] = c;
			j++;
			i++;
			mv[c] = i;
		}
	}
	/*map<char, int>::iterator iter;
	for (iter = mv.begin(); iter != mv.end(); iter++) {
		cout << iter->first << " : " << iter->second << endl;
	}*/
	/*for (i = 0; i < numvn; i++)
		cout << vn[i];*/
	cout << "输入文法:" << endl;
	for (i = 0; i < num; i++)
		cin >> grammar[i];
	string s;
	for (i = 0; i < num; i++)
	{
		s = grammar[i][0];
		for (int j = 3; j < grammar[i].length(); j++)
		{
			if (grammar[i][j] == '|')
			{
				vg.push_back(s);
				s.clear();
				s = grammar[i][0];
			}
			else
			{
				s = s + grammar[i][j];
			}
		}
		vg.push_back(s);
	}
	/*for (int j = 0; j < vg.size(); j++)
	{
		cout << vg[j] << " ";
	}
	cout << endl;*/
	//cout << numvn << endl;
}

void Grammar::remove_leftrecursion()
{

}

void Grammar::remove_leftcommon_factor()     //消除左公因式
{
	/*for (int i = 0; i < vg.size(); i++)    //遍历产生式，找出所有含有左公因式的
	{
		for (int j = i + 1; j < vg.size(); j++)      //每一个产生式和后面所有的产生式比较
		{
			prefix_match(vg[i], vg[j], vg, i, j);
		}
	}*/
}

//如果产生式右部的第一个字符是终结符号（VT），则其加入左部的first
//如果产生式右部的第一个字符是非终结符号（VN），则求该非终结符号的first，将该非终结符号的first集除去空加入左部的first，如有空则将产生式指针右移，如没有空则停止遍历，直至产生式最右部的非终结符号如还有空则把空加入左部first
void Grammar::getfirst()
{
	for (int i = 1; i <= numvt; i++)     //终结符，first集是其本身。
	{
		first[i] = first[i] + vt[i];
	}
	/*for (int i = 1; i <= numvt; i++)
		cout << first[i] << endl;*/
	/*for (int i = 0; i < vg.size(); i++)
	{
		cout << vg[i][0] << endl;
	}*/
	/*cout << numvn;
	for (int i = 0; i < numvn; i++)
	{
		cout << vn[i] << endl;
	}*/
	for (int i = 0; i < vg.size(); i++)     //遍历所有产生式
	{
		bool empty = 1;
		int k = 0;
		while (empty)
		{
			k++;
			empty = 0;
			if (k==vg[i].size())      //如果到了产生式末尾
			{
				//cout << vg[i][0] << endl;
				first[mv[vg[i][0]]] = first[mv[vg[i][0]]] + '$';
				break;
			}
			remove_dup(first[mv[vg[i][0]]], get_f(i, k, empty));
		}
	}
	for (int i = numvt + 1, k = 0; i <= numvt + numvn; i++, k++) 
	{
		cout << "first[" << vn[k] << "]:";
		for (int j = 0; j < first[i].size(); j++)
		{
			cout << first[i][j] << " ";
		}
		cout << endl;
	}
}

//如果产生式右部的非终结符号是终结符号，则加入该非终结符号的follow
//如果产生式右部的非终结符号是非终结符号其该非终结符号推不出空，则把这个非终结符的去空first加入其follow
//如果产生式右部的非终结符号在末尾或其右部的非终结符号能推导出空，则把产生式左部的非终结符的follow加入其follow
//如果是开始符号，则加#
void Grammar::getfollow()
{
	follow[mv[vn[0]]] = follow[mv[vn[0]]] + "#";
	for (int i = 0; i < vg.size(); i++)     //遍历所有产生式
	{
		for (int j = 1; j < vg[i].size(); j++)    //遍历当前产生式
		{
			if (if_vt(vg[i][j + 1]))
			{
				follow[mv[vg[i][j]]] = follow[mv[vg[i][j]]] + vg[i][j + 1];
			}
		}
	}
	for (int i = 0; i < vg.size(); i++)     //遍历所有产生式
	{
		for (int j = 1; j < vg[i].size(); j++)    //遍历当前产生式
		{
			bool empty = 1;
			int k = j;
			if (if_vn(vg[i][j]))       //如果是非终结符号
			{
				while (empty)
				{
					empty = 0;
					k++;
					if (k == vg[i].size())      //如果它是在末尾
					{
						remove_dup(follow[mv[vg[i][j]]], follow[mv[vg[i][0]]]);
						break;
					}
					remove_dup(follow[mv[vg[i][j]]], get_f(i, k, empty));
				}
			}
		}
	}
	/*for (int i = 0; i < numvn; i++)
	{
		remove_dup(follow[mv[vn[i]]], follow[mv[vn[i]]]);
	}*/
	for (int i = numvt + 1, k = 0; i <= numvt + numvn; i++, k++) 
	{
		cout << "follow[" << vn[k] << "]:";
		for (int j = 0; j < follow[i].size(); j++)
		{
			cout << follow[i][j] << " ";
		}
		cout << endl;
	}
}

void Grammar::gettable()        //构造预测分析表
{
	cout << "预测分析表：" << endl;
	for (int i = 0; i < vg.size(); i++)     //遍历所有产生式
	{
		if (vg[i][1] == '$')             //如果直接推出空，则求出其follow
		{
			string s = follow[mv[vg[i][0]]];
			for (int j = 0; j < follow[mv[vg[i][0]]].size(); j++)      //将follow集中的加入table
			{
				table[mv[vg[i][0]]][mv[s[j]]] = i;
			}
		}
		else
		{
			string fs = first[mv[vg[i][1]]];
			for (int j = 0; j < fs.size(); j++)    //遍历first
			{
				if (fs[j] != '$')       //如果推不出空，则该条产生式加入table
				{
					//cout << fs[j];
					// cout << mv[fs[j]] << endl;
					table[mv[vg[i][0]]][mv[fs[j]]] = i;
				}
				else
				{
					string s = follow[mv[vg[i][1]]];       //如果能推出空，则考虑后面的符号
					for (int k = 0; k < s.size(); k++)
					{
						table[mv[vg[i][0]]][mv[s[k]]] = i;
					}
				}
			}
		}
	}
	cout << setiosflags(ios::left);
	cout << setw(10)<<" ";
	for (int i = 0; i < numvt; i++)
	{
		cout << setw(10) << vt[i];
	}
	cout << endl;
	for (int i = 0, m = mv[vn[0]]; i < numvn; i++, m++) 
	{
		cout << setw(10) << vn[i];
		for (int j = 0, n = mv[vt[0]]; j < numvt; j++, n++) 
		{
			if (table[m][n] != 100)
			{
				/*cout << vg[table[m][n]][0] << "->";
				for (int k = 1; k < vg[table[m][n]].size(); k++)
					cout << vg[table[m][n]][k];*/
				string s = "";
				s = s + vg[table[m][n]][0] + "->";
				//string s = "";
				for (int k = 1; k < vg[table[m][n]].size(); k++)
					s = s + vg[table[m][n]][k];
				cout << setw(10) << s;
				//cout << " ";
			}
			if (table[m][n] == 100)
			{
				cout << setw(10)<<" ";
			}
			//cout << vn[i] << vt[j];
			//cout << table[m][n] << " ";
		}
		cout << endl;
	}
}

void Grammar::analyze()
{
	cout << "输入分析句子：";
	cin >> sentence;
	sentence = sentence + '#';
	stack<char> st;
	st.push('#');
	st.push(vg[0][0]);
	int i = 0;
	while (!st.empty())
	{
		char c = st.top();
		cout << c << " " << sentence[i] << endl;
		if (if_vt(c) && sentence[i] != '#')    //如果是终结符号
		{
			if (sentence[i] == c)    //匹配
			{
				st.pop();
				i++;
			}
			else
			{
				cout << "不是这个文法的句子" << endl;
				break;
			}
		}
		else if (if_vn(c))    //如果是非终结符
		{
			if (table[mv[c]][mv[sentence[i]]] < vg.size() && vg[table[mv[c]][mv[sentence[i]]]][1] != '$')      //找到该产生式
			{
				//cout << table[mv[c]][mv[sentence[i]]] << endl;
				st.pop();
				for (int j = vg[table[mv[c]][mv[sentence[i]]]].size() - 1; j >= 1; j--)   //逆序存入栈
				{
					//cout << vg[table[mv[c]][mv[sentence[i]]]];
					st.push(vg[table[mv[c]][mv[sentence[i]]]][j]);
				}
			}
			else if (vg[table[mv[c]][mv[sentence[i]]]][1] == '$')
			{
				st.pop();
			}
			else if (table[mv[c]][mv[sentence[i]]] == 100)     //无产生式，出错
			{
				cout << "不是这个文法的句子" << endl;
				break;
			}
		}
		else if (sentence[i] == '#')      //分析成功
		{
			cout << "是这个文法的句子" << endl;
			break;
		}
		else
		{
			cout << "不是这个文法的句子" << endl;
			break;
		}
	}
	
}

int main()
{
	Grammar g;
	g.init();
	g.remove_leftrecursion();
	g.getfirst();
	g.getfollow();
	if (g.if_LL1())
	{
		cout << "是LL（1）文法" << endl;
		g.gettable();
		g.analyze();
	}
	else
		cout << "不是LL（1）文法" << endl;
	system("pause");
    return 0;
}

/*int num,numvt=0,numvn=0;                 //文法条数，非终结符数，终结符数
char c;
int i = 0;
cout << "输入文法条数:";
cin >> num;
cout << "输入所有非终结符:";
while ((c = getchar()) != '@')         //输入到*结束输入
{
if ((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z'))
{
numvt++;
vn[i] = c;
i++;
}
}
i = 0;
cout << "输入所有终结符:";
while ((c = getchar()) != '@')
{
if (c >= 33 && c <= 127)
{
numvt++;
vt[i] = c;
i++;
}
}
cout << "输入文法:" << endl;
for (i = 0; i < num; i++)
cin >> grammar[i];
for (i = 0; i < num; i++)
cout << grammar[i] << endl;
leftrecursion(grammar);*/
//cout << numvn << endl;
//cout << vn[0] << endl;
//cout << numvt << endl;
//cout << vt << endl;