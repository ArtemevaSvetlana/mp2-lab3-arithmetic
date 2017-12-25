// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <string>

Lexem::Lexem()
{
	type=UNKNOWN;
	Val=0.0;
	Pr=-1;
	Op=0;
}

//================================================

Lexem::Lexem(char c)
{
	if (isdigit(c))
	{
		type = NUMBER;
		char s[2];
		s[0]=c;
		s[1]='\0';
		Val=atof(s);
		Op=0;
	}
	else
	{
		switch (c)
			{				
				case '(':
				{
					type=LEFTBR;
					Pr=0;
					Op=0;
					break;
				}
				case ')':
				{
					type=RIGHTBR;
					Op=0;
					break;
				}
				case '+':
				{
					type=OPERATOR;
					Pr=1;
					Op=1;
					break;
				}
				case '-':
				{
					type=OPERATOR;
					Pr=1;
					Op=2;
					break;
				}
				case '*':
				{
					type=OPERATOR;
					Pr=2;
					Op=3;
					break;
				}
				case '/':
				{
					type=OPERATOR;
					Pr=2;
					Op=4;
					break;
				}
				default:
					{
						type=UNKNOWN;
						Op=0;
					}
			}

	}
}

//================================================

Lexem::Lexem(const string &s)	//creating numbers_lexem
{
	int k=0;
	unsigned int i=0;
	if (s[0]=='-') 
	{
			k++;
			i++;
	}
	for (i; i<s.length(); i++)
	{	
		if ((isdigit(s[i])) || (s[i]=='.'))
			k++;
	}
	if (k==s.length())
	{
		Val = stod(s);
		Op=0;
		type = NUMBER;
	}
	else
		throw "Error!";
}

//================================================

Lexem::Lexem(const Lexem &lex)
{
	type=lex.type;
	Pr=lex.Pr;
	Val=lex.Val;
	Op=lex.Op;
}

//================================================

bool Lexem::operator==(const Lexem &lex) const
{
	if (type==lex.type)
	{
		if (type==NUMBER)
		{
			if (Val==lex.Val)
				return true;
			else 
				return false;
		}
		else if(type==OPERATOR)
		{
			if ((Pr==lex.Pr) && (Op==lex.Op) && (Op>0) && (Op<5))
				return true;
			else 
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

//================================================

void Lexem::operator=(const Lexem &lex)
{
	type=lex.type;
	Val=lex.Val;
	Pr=lex.Pr;
	Op=lex.Op;
}

//================================================

Arithmetic::Arithmetic(const string &s)
{ 
	if (s=="")
		throw "Error!";
	
	flag=false;
	str=s;
	int Size=s.length();
	pLex=new Lexem[2*Size];
	
	std::string s1;
	int k=0;		//nLex
	char c;

	bool un=false;
	int i=0;

	if ( (str[0]=='-') && (isdigit(str[1])) )
	{
		un=true;
		i++;
	}

	for (int i=0; i<Size; i++)
	{	

		if ((str[i]=='-') && (str[i-1]=='('))
		{
			un=true;
			i++;
		}
		int j=i;
		c=str[j];
		if (isdigit(c))
		{
			while (((isdigit(str[j])) || (str[j]=='.')) && (j<Size))
					j++;
			
			if (un)
			{
				i--;
				un=false;
			}
			
			s1=str.substr(i,j-i);
			Lexem t(s1);
			pLex[k]=t;
			i=j-1;
		}
		else
		{
			Lexem t(c);			
			pLex[k]=t;	
		} 

		k++;
	}
	nLex=k;
}

//================================================

Arithmetic::Arithmetic(const Arithmetic &t)
{
	str=t.str;
	nLex=t.nLex;

	pLex= new Lexem[nLex];		
	for (int i=0;i<nLex;i++)
		pLex[i]=t.pLex[i];
	
	flag=t.flag;
	if (flag)
	{
		npolLex=t.npolLex;
		polLex= new Lexem[npolLex];
		for (int i=0;i<npolLex;i++)
			polLex[i]=t.polLex[i];
	}
}

//================================================

Arithmetic::~Arithmetic()
{
	delete [] pLex;
	if (flag)
		delete [] polLex;
}

//================================================

bool Arithmetic::operator==(const Arithmetic &t) const
{
	if (str==t.str)
	{
		if (nLex!=t.nLex)
			return false;
		else
		{
			for (int i=0;i<nLex;i++)
				if (!(pLex[i]==t.pLex[i]))
					return false;
		}

		if (flag==t.flag)
		{
			if (flag)
			{
				if (npolLex==t.npolLex)
					for (int i=0;i<npolLex;i++)
						if (!(polLex[i]==t.polLex[i]))
							return false;
			}
		}
		else
			return false;
	}
	else 
		return false;
	return true;
}

//================================================

int Arithmetic::GetnLex()
{
	return nLex;
}

//================================================

Lexem Arithmetic::GetLex(int i)
{
	if ((i<1) || (i>nLex))
		throw "Error!";
	
	return pLex[i-1];
}

//================================================

void Arithmetic::PolEnt()
{
	flag=true;
	TStack<Lexem> stack(nLex*2);
	polLex= new Lexem[nLex*2];
	int j=0;

	for (int i=0;i<nLex;i++)
	{
		if (pLex[i].type==NUMBER)
				polLex[j++]=pLex[i];
				
		if (pLex[i].type==LEFTBR)
				stack.Push(pLex[i]);
	
		if (pLex[i].type==RIGHTBR)
			{
				while (stack.GetElem().type != LEFTBR)
						polLex[j++]=stack.Pop();
				stack.Pop();		
			}
		
		if (pLex[i].type==OPERATOR)
		{
			if (stack.IsEmpty())
				stack.Push(pLex[i]);
			else
			{
				Lexem t = stack.GetElem();
				while (!stack.IsEmpty() && (t.Pr >= pLex[i].Pr))
				{
					t = stack.Pop();
					polLex[j++] = t;
					if (!stack.IsEmpty())
						t = stack.GetElem();
				}
				stack.Push(pLex[i]);
			}
		}
	}

	while (!stack.IsEmpty())
		polLex[j++]=stack.Pop();

	
		npolLex=j;
}
 
//================================================

double Arithmetic::CalcPolEntr()
{
	if (!flag)
		throw "Error!";	
	
	TStack<double> st(npolLex);
	double res=0;

	for (int i=0;i<npolLex;i++)
	{
		if (polLex[i].type==NUMBER)
			st.Push(polLex[i].Val);
		else
			if (polLex[i].type==OPERATOR)
			{
				double a=st.Pop();
				double b=st.Pop();

				switch (polLex[i].Op)
				{
					case 1:
					{
						res=b+a;
						break;
					}
					case 2:
					{
						res=b-a;
						break;
					}
					case 3:
					{
						res=b*a;
						break;
					}
					case 4:
					{
						if (a==0.0)
							throw "Error!";
						else
							res=b/a;
						break;
					}
				}

				st.Push(res);
			}
	}
	return st.Pop();
}

//================================================

int Arithmetic::GetnPolLex()
{
	return npolLex;
}

//================================================

Lexem Arithmetic::GetPolLex(int n)
{
	if ((n<1) || (npolLex==0) || (n>npolLex))
		throw "Error!";

	return polLex[n-1];
}

//================================================

bool Arithmetic::CheckBrackets()
{
	int check=0;
	for (unsigned int i=0;i<str.length();i++)
	{
		if (str[i]=='(')
			check++;
		if (str[i]==')')
			check--;
		if (check==-1)
			return false;
	}

	if (check!=0)
	{
		cout<<"\n"<<"Error! Wrong brackets!"<<endl;
		return false;
	}
	else
		return true;
}

//===============================================

bool Arithmetic::CheckLetters()
{	
	for (int i=0;i<nLex;i++)
	{
		if (pLex[i].type==UNKNOWN)
		{
			cout<<"\n"<<"Error! Unknown symbol! Check "<<i+1<<" symbol!"<<endl;
			return false;
		}
	}
	return true;
}
//===============================================

bool Arithmetic::CheckOperators()
{
	std::string s="Error! Wrong order of symbols! Check ";

	if (pLex[0].type==RIGHTBR)
	{
		cout<<"\n"<<"Error! Can't start from close bracket!"<<endl;
		return false;
	}
	else if (pLex[0].type==OPERATOR)
	{
		cout<<"\n"<<"Error! Can't start from operation!"<<endl;
		return false;
	}

	for (int i=0;i<nLex-1;i++)
	{
		Lexem cur=pLex[i];
		Lexem next=pLex[i+1];
		if (cur.type==NUMBER)
		{
			if ((next.type==LEFTBR) || (next.type==NUMBER))
			{
				cout<<"\n"<<s<<i+1<<" term"<<endl;
				return false;
			}
		}

		else if (cur.type==OPERATOR)
		{
			if ((next.type==OPERATOR) || (next.type==RIGHTBR))
			{
				cout<<"\n"<<s<<i+2<<" term"<<endl;
				return false;
			}

			if ((cur.Op==4) && (next.type==NUMBER))
			{
				if (next.Val==0.0)
				{
					cout<<"\n"<<"Error! You can't divide by zero!"<<endl;
					return false;
				}
			}
		}

		else if (cur.type==LEFTBR)
		{
			if ( ( (next.type==OPERATOR) && (next.Op!=2) )  || (next.type==RIGHTBR))
			{
				cout<<"\n"<<s<<i+2<<" term"<<endl;
				return false;
			}
		}

		else if (cur.type==RIGHTBR)
		{
			if ((next.type==LEFTBR) || (next.type==NUMBER))
			{
				cout<<"\n"<<s<<i+2<<" term"<<endl;
				return false;
			}
		}
	}

	if ((pLex[nLex-1].type==OPERATOR) || (pLex[nLex-1].type==LEFTBR))
	{
		cout<<"\n"<<s<<nLex<<" term"<<endl;
		return false;
	}
	else
	return true;
}

//===============================================

bool Arithmetic::CheckAll()
{
	bool lt=CheckLetters();
	bool oper=CheckOperators();
	bool br=CheckBrackets();
	
	return (lt&&oper&&br);	
}



