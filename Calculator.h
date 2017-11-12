#pragma once
#include<iostream>
#include<stack>
#include <iomanip>
using namespace std;
class Calculate
{
public:
	void run();
private:
	stack<double> OPND;
	stack<char> OPTR;
	void GetChar(char& ch);
	bool IsOperator(char ch);
	int isp(char op);                        //栈内优先数
	int icp(char op);                        //栈外优先数
	double DoOperator(double x, char op, double y);              //形成运算指令，进行运算
};

void Calculate::run()
{
	double temp;
	char n;
	cout << "请输入一个算术表达式:" << endl;
	GetChar(n);
	OPTR.push('=');
	while (n != '=' || OPTR.top() != '=')
	{
		//当输入数字时，从输入流压入栈OPND
		if ((n >= '0' && n <= '9') || n == '.')
		{
			cin.putback(n);
			cin >> temp;
			OPND.push(temp);
		}
		else
		{
			//若操作符非法，打印错误
			if (!IsOperator(n))
				cout << "error operator!!!" << endl;
			else
			{
				//若当前操作符为），将计算（）内的值并压入栈顶
				if (n == ')')
				{
					while (OPTR.top() != '(')
					{
						char temp1 = OPTR.top();
						OPTR.pop();
						double x = OPND.top();
						OPND.pop();
						double y = OPND.top();
						OPND.pop();
						OPND.push(DoOperator(y, temp1, x));
					}
					OPTR.pop();
				}
				else
				{
					//当输入运算符的栈外优先级大于栈顶运算符的栈内优先级，将输入运算符压入栈顶
					if (icp(n) > isp(OPTR.top()))
					{
						OPTR.push(n);
					}
					else
					{
						//当输入运算符的栈外优先级小于或等于栈顶运算符的栈内优先级，从栈顶取出操作数运算直至
						//当前运算符的栈外优先级大于栈顶运算符的栈内优先级，并压入栈顶
						while (icp(n) <= isp(OPTR.top()))
						{
							if (n == '=' && OPTR.top() == '=')
							{
								cout << OPND.top() << endl;
								return;
							}						
							char temp1 = OPTR.top();
							OPTR.pop();
							double x = OPND.top();
							OPND.pop();
							double y = OPND.top();
							OPND.pop();
							OPND.push(DoOperator(y, temp1, x));
						}
						OPTR.push(n);
					}
				}
			}
		}
		GetChar(n);
	}
	//遇到‘=’时跳出循环并从栈顶取出操作数和运算符进行计算
	char temp1 = OPTR.top();
	OPTR.pop();
	double x = OPND.top();
	OPND.pop();
	double y = OPND.top();
	OPND.pop();
	OPND.push(DoOperator(y, temp1, x));
	cout.setf(ios::fixed);
	cout << setprecision(2) << OPND.top() << endl;
	cout.unsetf(ios::fixed);
}


//栈外优先数
int Calculate::icp(char op)
{
	int count;
	switch (op)
	{
	case '=': count = 0; break;
	case '(': count = 6; break;
	case '+': case '-': count = 3; break;
	case '*': case '/': count = 5; break;
	case ')': count = 7; break;
	}
	return count;
}

// 栈内优先数
int Calculate::isp(char op)
{
	int count;
	switch (op)
	{
	case '=': count = 0; break;
	case '(': count = 2; break;
	case '+': case '-': count = 3; break;
	case '*': case '/': count = 5; break;
	}
	return count;
}


double Calculate::DoOperator(double x, char op, double y)
{
	switch (op)
	{
	case '+': return x + y; break;
	case '-': return x - y; break;
	case '*': return x * y; break;
	case '/': return x / y; break;
	}
	return -1;
}

void Calculate::GetChar(char & ch)
{
	ch = cin.get();
	while (ch == ' ' || ch == '\n')
		ch = cin.get();

}

bool Calculate::IsOperator(char ch)
{
	if (ch == '(' || ch == ')' || ch == '+' || ch == '-' ||
		ch == '*' || ch == '/' || ch == '=')
		return true;
	else
		return false;
}
