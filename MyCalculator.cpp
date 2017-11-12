// MyCalculator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include "Calculator.h"
using namespace std;

int main()
{
	Calculate cal;
	while (true)
	{
		cal.run();
		char f;
		cout << "是否继续输入Y/N" << endl;
		cin >> f;
		if (f == 'Y')
			continue;
		else
			break;
	}
    return 0;
}
