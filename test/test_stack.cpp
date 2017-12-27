// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> st(3));
}

TEST(TStack, can_not_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> st(MAX_SIZE_STACK+1));
}

TEST(TStack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> st(5);
	ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> st1(4);
	
		st1.Push(1);
		st1.Push(3);
		st1.Push(2);

	TStack<int> st2(st1);

	EXPECT_EQ(st1, st2);
	EXPECT_EQ(2, st2.Pop());
	EXPECT_EQ(3, st2.Pop());
	EXPECT_EQ(1, st2.Pop());
}

TEST(TStack, can_pop_elem)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	int a=st.Pop();
	EXPECT_EQ(2,a);
}

TEST(TStack, can_pop_and_delete_elem_)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	int a=st.Pop();

	EXPECT_EQ(1, st.NumEl());
}

TEST(TStack, can_not_pop_empty_stack)
{
	TStack<int> st(2);
	int a=0;

	ASSERT_ANY_THROW(a=st.Pop());
}

TEST(TStack, can_get_elem)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);
	int a=0;
	EXPECT_EQ(2,a=st.GetElem());
}

TEST(TStack, can_not_get_elem_if_stack_empty)
{
	TStack<int> st(1);
	st.Push(1);
	int a=st.Pop();

	ASSERT_ANY_THROW(st.GetElem());
}

TEST(TStack, can_push_elem_1)
{
	TStack<int> st(3);
	st.Push(1);
	int a=0;
	EXPECT_EQ(1, st.GetElem());
}

TEST(TStack, can_push_elem_2)
{
	TStack<int> st(3);
	st.Push(1);
	st.Push(2);
	
	EXPECT_EQ(2, st.NumEl());
}

TEST(TStack, can_push_if_stack_is_full)
{
	TStack<int> st(2);
	st.Push(2);
	st.Push(3);
	st.Push(4);

	EXPECT_EQ(3, st.NumEl());
}

TEST(TStack, can_not_compare_stacks_with_different_size)
{
	TStack<int> st1(1), st2(2);

	EXPECT_EQ(false, st1==st2);
}

TEST(TStack, can_not_compare_stacks_with_different_numel)
{
	TStack<int> st1(2), st2(2);
	st1.Push(1);
	st1.Push(2);

	st2.Push(1);

	EXPECT_EQ(false, st1==st2);
}

TEST(TStack, can_compare_equal_stck)
{
	TStack<int> st1(2);
	st1.Push(1);
	TStack<int> st2(st1);

	EXPECT_EQ(true, st1==st2);
}

TEST(TStack, can_compare_not_equal_stack)
{
	TStack<int> st1(2), st2(2);
	st1.Push(1);
	st1.Push(2);
	
	st2.Push(1);
	st2.Push(5);

	EXPECT_EQ(false, st1==st2);
}

TEST(TStack, check_empty_stack)
{
	TStack<int> st(1);
	st.Push(1);
	int a=st.Pop();
	
	EXPECT_EQ(true, st.IsEmpty());
}

TEST(TStack, check_not_empty_stack)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(2);

	EXPECT_EQ(false, st.IsEmpty());
}

TEST(TStack, check_full_stack)
{
	TStack<int> st(2);
	st.Push(4);
	st.Push(3);

	EXPECT_EQ(true, st.IsFull());
}

TEST(TStack, check_not_full_stack)
{
	TStack<int> st(2);
	st.Push(1);

	EXPECT_EQ(false, st.IsFull());
}

TEST(TStack, check_top_with_empty_stack)
{
	TStack<int> st(1);
	st.Push(3);
	int a=st.Pop();

	EXPECT_EQ(0,st.NumEl());
}

TEST(TStack, check_number_of_elements_in_stack)
{
	TStack<int> st(3);
	st.Push(3);
	st.Push(3);

	EXPECT_EQ(2, st.NumEl());
}

TEST(TStack, check_number_of_elements_in_full_stack)
{
	TStack<int> st(2);
	st.Push(3);
	st.Push(2);

	EXPECT_EQ(2, st.NumEl());
}

TEST(TStack, clear_stack)
{
	TStack<int> st(2);
	st.Push(2);
	st.Clear();

	EXPECT_EQ(0, st.NumEl());
}

TEST(TStack, can_not_get_elem_from_cleared_stack)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(3);
	st.Clear();

	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, can_not_pop_elem_from_cleared_stack)
{
	TStack<int> st(2);
	st.Push(1);
	st.Push(3);
	st.Clear();

	ASSERT_ANY_THROW(st.GetElem());
}












