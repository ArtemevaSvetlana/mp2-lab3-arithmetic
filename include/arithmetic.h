// объ€вление функций и классов дл€ вычислени€ арифметических выражений

#include <iostream>
#include "stack.h"

using namespace std;

enum LexemType {NUMBER, LEFTBR, RIGHTBR, OPERATOR, UNKNOWN};

struct Lexem 
{
	LexemType type;
	double Val;
	int Pr;
	int Op;

	Lexem();
	Lexem(char c);
	Lexem(const string &str);
	Lexem(const Lexem &lex);
	void operator=(const Lexem &lex);
	bool operator==(const Lexem &lex) const;
};


class Arithmetic
{
	Lexem *pLex;
	std::string str;
	int nLex;
	Lexem *polLex;
	int npolLex;
	bool flag;

	public:
		Arithmetic(const string &s);
		Arithmetic(const Arithmetic &t);
		~Arithmetic();

		bool operator==(const Arithmetic &t) const;
		int GetnLex();
		Lexem GetLex(int n);
		
		void PolEnt();
		double CalcPolEntr();

		int GetnPolLex();
		Lexem GetPolLex(int n);

		bool CheckBrackets();
		bool CheckLetters();
		bool CheckOperators();
		bool CheckAll();
};
