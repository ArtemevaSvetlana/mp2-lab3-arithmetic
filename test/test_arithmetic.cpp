// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(Lexem, can_create_lexem_without_anything)
{
	ASSERT_NO_THROW(Lexem t);
}

TEST(Lexem, can_create_lexem_without_anything_2)
{
	Lexem t;
	EXPECT_EQ(UNKNOWN, t.type);
	EXPECT_EQ(0, t.Val);
	EXPECT_EQ(-1, t.Pr);

	EXPECT_EQ(0, t.Op);
}

TEST(Lexem, can_create_lexem_with_char)
{
	char c=' ';
	ASSERT_NO_THROW(Lexem t(c));
}

TEST(Lexem, can_create_lexem_with_char_2)
{
	char c='(';
	Lexem t(c);
	EXPECT_EQ(LEFTBR, t.type);
	EXPECT_EQ(0, t.Pr);

	c=')';
	Lexem a(c);
	EXPECT_EQ(RIGHTBR, a.type);

	c='-';
	Lexem b(c);
	EXPECT_EQ(OPERATOR, b.type);
	EXPECT_EQ(1, b.Pr);
	EXPECT_EQ(2, b.Op);

	c='+';
	Lexem v(c);
	EXPECT_EQ(OPERATOR, v.type);
	EXPECT_EQ(1, v.Pr);
	EXPECT_EQ(1,v.Op);
	
	c='*';
	Lexem n(c);
	EXPECT_EQ(OPERATOR, n.type);
	EXPECT_EQ(2, n.Pr);
	EXPECT_EQ(3,n.Op);

	c='/';
	Lexem z(c);
	EXPECT_EQ(OPERATOR, z.type);
	EXPECT_EQ(2, z.Pr);
	EXPECT_EQ(4,z.Op);

	c='j';
	Lexem m(c);
	EXPECT_EQ(UNKNOWN, m.type);
	
}

TEST(Lexem, can_create_number_lexem)
{
	std::string str="123", str2="1.78907";

	ASSERT_NO_THROW(Lexem t(str));
	ASSERT_NO_THROW(Lexem t(str2));
}

TEST(Lexem, can_create_number_lexem_2)
{
	std::string str="-123";
	Lexem t(str);

	EXPECT_EQ(-123, t.Val);
	EXPECT_EQ(NUMBER, t.type);
}

TEST(Lexem, can_not_create_number_lexem_if_type_is_not_number)
{
	std::string str="53-2";
	
	ASSERT_ANY_THROW(Lexem t(str));
	
	str="dks";
	ASSERT_ANY_THROW(Lexem t(str));

	str="23f";
	ASSERT_ANY_THROW(Lexem t(str));
}

TEST(Lexem, can_create_copied_lexem)
{
	Lexem t;
	ASSERT_NO_THROW(Lexem z(t));
}

TEST(Lexem, copied_lexem_is_equal_to_source_one)
{
	std::string str1="1234";
	char c1='-', c2='k', c3='4'; 

	Lexem t1, z1(str1), v1(c1), k1(c2), q1(c3);

	Lexem t2(t1), z2(z1), v2(v1), k2(k1), q2(q1);

	EXPECT_EQ(t1, t2);
	EXPECT_EQ(z1, z2);
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(k1, k2);
	EXPECT_EQ(q1, q2);
}

TEST(Lexem, can_compare_lexems)
{
	std::string str1="123";
	char c1='/', c2='r', c3='(', c4=')';
	Lexem t1(str1), t2(t1);
	Lexem q1(c1), q2(q1);
	Lexem z1(c2), z2(z1);
	Lexem v1(c3), v2(v1);
	Lexem k1(c4), k2(k1);

	EXPECT_EQ(true, t1==t2);
	EXPECT_EQ(true, z1==z2);
	EXPECT_EQ(true, v1==v2);
	EXPECT_EQ(true, k1==k2);
	EXPECT_EQ(true, q1==q2);
	EXPECT_EQ(true, z1==z2);
	
	EXPECT_EQ(false, z1==q2);
}

TEST(Lexem, can_assign_lexems)
{
	std::string str="123";
	char c='9';

	Lexem t1(str), t2;
	Lexem z1(c), z2;
	
	ASSERT_NO_THROW(z1=z2);
	ASSERT_NO_THROW(t1=t2);
}

TEST(Lexem, assigned_lexem_is_equal_to_source_one)
{
	std::string str="123";
	char c='9';
	
	Lexem t1(str), t2;
	Lexem z1(c), z2;

	t2=t1;
	z2=z1;

	EXPECT_EQ(true,t1==t2);
	EXPECT_EQ(true,z1==z2);
}

//=====================================================

TEST(Arithmetic, can_create_arithmetic)
{
	std::string str="11+12";
	ASSERT_NO_THROW(Arithmetic t(str));

	str="-1+5*(2-1)/88.8";
	ASSERT_NO_THROW(Arithmetic t(str));
		
}

TEST(Arithmetic, created_arithmetic_is_right)
{
	string str="-1+5*(2-1)/88.8";
	Arithmetic t(str);

	EXPECT_EQ(11, t.GetnLex());

	char c2='+', c3='5';
	char c4='*', c5='(', c6='2', c7='-';
	char c8='1', c9=')', c10='/';
	string c1="-1", c11="88.8";
	
	Lexem z1(c1), z2(c2), z3(c3);
	Lexem z4(c4), z5(c5), z6(c6), z7(c7);
	Lexem z8(c8), z9(c9), z10(c10), z11(c11);

	EXPECT_EQ(z1, t.GetLex(1));
	EXPECT_EQ(z2, t.GetLex(2));
	EXPECT_EQ(z3, t.GetLex(3));
	EXPECT_EQ(z4, t.GetLex(4));
	EXPECT_EQ(z5, t.GetLex(5));
	EXPECT_EQ(z6, t.GetLex(6));
	EXPECT_EQ(z7, t.GetLex(7));
	EXPECT_EQ(z8, t.GetLex(8));
	EXPECT_EQ(z9, t.GetLex(9));
	EXPECT_EQ(z10, t.GetLex(10));
	EXPECT_EQ(z11, t.GetLex(11));

	str="(-9-8)";
	Arithmetic t1(str);
	string c="-9";

	Lexem v1('('), v2(c), v3('-'), v4('8'), v5(')');

	EXPECT_EQ(5, t1.GetnLex());

	EXPECT_EQ(v1, t1.GetLex(1));
	EXPECT_EQ(v2, t1.GetLex(2));
	EXPECT_EQ(v3, t1.GetLex(3));
	EXPECT_EQ(v4, t1.GetLex(4));
	EXPECT_EQ(v5, t1.GetLex(5));
}

TEST(Arithmetic, can_not_create_arithmetic_from_empty_string)
{
	std::string str="";

	ASSERT_ANY_THROW(Arithmetic t(str));
}

TEST(Arithmetic, can_get_nLex)
{
	std::string str="-1+5*(2-1)/88.8";
	Arithmetic t(str);

	EXPECT_EQ(11, t.GetnLex());
}

TEST(Arithmetic, can_get_lexem)
{
	std::string str="-1+5*(-2-1)/88.8";
	Arithmetic t(str);
	
	EXPECT_EQ(-1, t.GetLex(1).Val);
}

TEST(Arithmetic, can_not_get_lexem_with_wrong_index)
{
	std::string str="9-7";
	Arithmetic t(str);

	ASSERT_ANY_THROW(t.GetLex(0));
	ASSERT_ANY_THROW(t.GetLex(4));
}

TEST(Arithmetic, can_not_get_lexem_with_negative_index)
{
	std::string str="2-1";
	Arithmetic t(str);

	ASSERT_ANY_THROW(t.GetLex(-7));
}

TEST(Arithmetic, can_make_polish_entry)
{
	std::string str="(-2-1)";
	Arithmetic t(str);

	EXPECT_EQ(5, t.GetnLex());

	ASSERT_NO_THROW(t.PolEnt());
}

TEST(Arithmetic, polish_entry_is_right)
{
	std::string str="5+3";
	Arithmetic t(str);	

	t.PolEnt();

	EXPECT_EQ(3, t.GetnPolLex());

	char c1='5', c2='+', c3='3';
	Lexem t1(c1), t2(c2), t3(c3);
	
	EXPECT_EQ(t1, t.GetPolLex(1));
	EXPECT_EQ(t3, t.GetPolLex(2));
	EXPECT_EQ(t2, t.GetPolLex(3));

	ASSERT_ANY_THROW(t.GetPolLex(4));
//==========================================
	std::string str1="1-5*(9-8)*3-1";		//polish_entry: {1, 5, 9, 8, -, *,}
	Arithmetic z(str1);

	z.PolEnt();

	EXPECT_EQ(11, z.GetnPolLex());

	char k1='1', k2='5', k3='9', k4='8';
	char k5='-', k6='*', k7='3'; 
	Lexem v1(k1), v2(k2), v3(k3), v4(k4);
	Lexem v5(k5), v6(k6), v7(k7);

	EXPECT_EQ(v1, z.GetPolLex(1));
	EXPECT_EQ(v2, z.GetPolLex(2));
	EXPECT_EQ(v3, z.GetPolLex(3));
	EXPECT_EQ(v4, z.GetPolLex(4));
	EXPECT_EQ(v5, z.GetPolLex(5));
	EXPECT_EQ(v6, z.GetPolLex(6));
	EXPECT_EQ(v7, z.GetPolLex(7));
	EXPECT_EQ(v6, z.GetPolLex(8));
	EXPECT_EQ(v5, z.GetPolLex(9));
	EXPECT_EQ(v1, z.GetPolLex(10));
	EXPECT_EQ(v5, z.GetPolLex(11));

	ASSERT_ANY_THROW(t.GetPolLex(12)); 
}

TEST(Arithmetic, can_create_copied_arithmetic)
{
	std::string str="7-3*10-1";
	Arithmetic t1(str);

	ASSERT_NO_THROW(Arithmetic t2(t1));
}

TEST(Arithmetic, copied_arithmetic_is_equal_to_source_one)
{
	std::string str="11+1.2";
	Arithmetic t1(str);	
	Arithmetic t2(t1);

	EXPECT_EQ(t1,t2);
}

TEST(Arithmetic, can_compare_arithmetic)
{
	std::string str="11+1.2";
	Arithmetic t1(str);	
	Arithmetic t2(t1);	

	EXPECT_EQ(true, t1==t2);

	std::string str1="1+1.2";
	Arithmetic z1(str);	
	Arithmetic z2(str1);

	EXPECT_EQ(false, z1==z2);

	z1.PolEnt();
	EXPECT_EQ(false, z1==z2);

	t1.PolEnt();
	EXPECT_EQ(false, t1==t2);

	t2.PolEnt();
	EXPECT_EQ(true, t1==t2);
}

TEST(Arithmetic, can_calculate_polish_entry)
{
	std::string str="(-5-8)";
	Arithmetic t(str);

	t.PolEnt();
	ASSERT_NO_THROW(t.CalcPolEntr());
}

TEST(Arithmetic, calculating_is_right)
{
	std::string str="5-8";
	Arithmetic t1(str);
	t1.PolEnt();
	
	EXPECT_EQ(-3, t1.CalcPolEntr());

	str="1.2+6";
	Arithmetic t2(str);
	t2.PolEnt();

	EXPECT_EQ(7.2, t2.CalcPolEntr());

	str="4/2";
	Arithmetic t3(str);
	t3.PolEnt();

	EXPECT_EQ(2, t3.CalcPolEntr());

	str="(5+8-(3+5*7)-5)/2";
	Arithmetic t4(str);
	t4.PolEnt();

	EXPECT_EQ(-15, t4.CalcPolEntr());
}


TEST(Arithmetic, can_not_calculate_withot_numbers_and_operators)
{
	std::string str="()-+/";
	Arithmetic t(str);
	t.PolEnt();
	ASSERT_ANY_THROW(t.CalcPolEntr());
}

TEST(Arithmetic, can_not_calculate_withot_poish_entry)
{
	std::string str="1-2";
	Arithmetic t(str);

	ASSERT_ANY_THROW(t.CalcPolEntr());
}

TEST(Arithmetic, can_get_npolLex)
{
	std::string str="1+4-(3+2)";
	Arithmetic t(str);
	t.PolEnt();
	
	EXPECT_EQ(7, t.GetnPolLex());
}

TEST(Arithmetic, can_not_get_polLex_with_wrong_index)
{
	std::string str="1+3";
	Arithmetic t(str);
	t.PolEnt();

	ASSERT_ANY_THROW(t.GetPolLex(0));
	ASSERT_ANY_THROW(t.GetPolLex(4));
}

TEST(Arithmetic, can_check_brackets)
{
	std::string str="(1-3)*7";
	Arithmetic t1(str);
	
	EXPECT_EQ(true, t1.CheckBrackets());

	str="((-7)";
	Arithmetic t2(str);
	EXPECT_EQ(false, t2.CheckBrackets());

	str="(-7))";
	Arithmetic t3(str);
	EXPECT_EQ(false, t3.CheckBrackets());
}

TEST(Arithmetic, can_check_letters)
{
	std::string str="7@+5";
 	Arithmetic t(str);

 	EXPECT_EQ(false, t.CheckLetters());

 	std::string str1="9-8";
 	Arithmetic t1(str1);
 	EXPECT_EQ(true, t1.CheckLetters());
}

TEST(Arithmetic, can_check_operators)
{
	string str="(-2-3)";
	Arithmetic t(str);

	EXPECT_EQ(true, t.CheckOperators());
	
	
	string str1=")76-8";
	Arithmetic t1(str1);
	EXPECT_EQ(false, t1.CheckOperators());
	
	string str2="*9-6";
	Arithmetic t2(str2);
	EXPECT_EQ(false, t2.CheckOperators());

	string str3="9/0";
	Arithmetic t3(str3);
	EXPECT_EQ(false, t3.CheckOperators());
	
	string str4="4(-";
	Arithmetic t4(str4);
	EXPECT_EQ(false, t4.CheckOperators());

	string str6="5-)";
	Arithmetic t6(str6);
	EXPECT_EQ(false, t6.CheckOperators());

	string str7="5*(+9)";
	Arithmetic t7(str7);
	EXPECT_EQ(false, t7.CheckOperators());

	string str9="(5-8)2";
	Arithmetic t9(str9);
	EXPECT_EQ(false, t9.CheckOperators());
}

TEST(Arithmetic, can_check_all_string)
{
	string str="5-4/";
	Arithmetic t1(str);
	
	EXPECT_EQ(false, t1.CheckAll());
}