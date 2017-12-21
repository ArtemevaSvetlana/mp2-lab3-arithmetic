// реализация пользовательского приложения

#pragma once
#include <iostream>
#include "arithmetic.h"
#include <string>
using namespace std;

int main()
{
	string str;
	int k=1;
	int j;
	bool flag=false;

	cout<<"		CALCULATING AN ARITHMETICAL EXPRESSION"<<endl;
	cout<<"\n"<<"Input number to choose the action:"<<endl;

	while (k==1)
	{
		if (!flag)
		{
			cout<<"\n"<<"1 - Enter an expression."<<endl;
			cout<<"2 - Exit."<<endl;
			cin>>j;
		}
		flag=true;

		switch (j)
		{
			case 1:
			{
				system("cls");
				cout<<"Enter an expression. Remember you can use only '+', '-', '*' and '/' operations."<<endl;
				cout<<"\n";
				cin>>str;

				while ((str==""))
				{
					cout<<"\n"<<"Expression is empty! Try again!";
					system("cls");
					cout<<"Enter an expression. Remember you can use only '+', '-', '*' and '/' operations."<<endl;
					cout<<"\n";
					cin>>str;
				}
				Arithmetic t(str);
				if (!t.CheckAll())
				{
					cout<<"\n"<<"There were errors in your expression."<<endl;
					cout<<"\n"<<"If you want to try again input 1."<<endl;
					cout<<"\n"<<"If you want to finish input 2."<<endl;
					cin>>j;
					k=j;
				}
				else
				{
					t.PolEnt();
					double res=t.CalcPolEntr();
					cout<<"\n"<<str<<"="<<res<<endl;
					cout<<"\n"<<"Input the command:"<<endl;
					cout<<"\n"<<"1-Try again."<<endl;
					cout<<"\n"<<"2-Exit."<<endl;
					cin>>j;
					k=j;
					flag=true;
				}
				break;
			}
			case 2:
			{
				k=2;
				break;
			}
			default:
			{
				flag=false;
				cout<<"\n"<<"There is no such command! Try again!"<<endl;
			}
		}
	}

}
