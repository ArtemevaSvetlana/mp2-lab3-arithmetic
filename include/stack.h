// объ€вление и реализаци€ шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удалени€)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыдел€тьс€ пам€ть
//--------------------------------------------------------

#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>
using namespace std;

const int MAX_SIZE_STACK=1000;

template <class T>


class TStack
{
	protected:
		T *pStack;
		int Size;
		int Top;	//индес последнего эл-та
	public:
		TStack(int s);
		TStack(const TStack &st);//конструктор копировани€
		~TStack();

		T Pop();	// извлечь эл-нт с удалением
		T GetElem();//посмотреть последний эл-нт
		void Push(T elem);//вставить эл-нт

		bool operator==(const TStack &st) const;
		TStack<T> & operator=(const TStack &st);

		bool IsEmpty();//проверка на пустоту
		bool IsFull();//проверка на заполненность
		int NumEl();//вернуть номер последнего эл-та
		void Clear();//очистить стек

};

//--------------------------------------------------------

template <class T> 
TStack<T>::TStack(int s)
{
	Size=s;
	if((Size<0)||(Size>MAX_SIZE_STACK))
		throw "Error!";
		pStack= new T[Size];
	Top=-1;
}

//--------------------------------------------------------

template <class T>
TStack<T>::TStack(const TStack &st)
{
	Size=st.Size;
	Top=st.Top;
	pStack= new T[Size];
	for (int i=0;i<Top;i++)
		pStack[i]=st.pStack[i];
}

//--------------------------------------------------------

template <class T>
TStack<T>::~TStack()
{
	delete []pStack;
}

//--------------------------------------------------------

template <class T>
T TStack<T>::Pop()		//извлечь с удалением
{
	if (IsEmpty())
		throw "Error!";
	else
		return pStack[Top--];
}

//--------------------------------------------------------

template <class T>
T TStack<T>::GetElem()
{
	if (IsEmpty())
		throw "Error!";
	
	return pStack[Top];
}

//--------------------------------------------------------

template <class T>
void TStack<T>::Push(T elem)		//вставить эл-нт
{
	if (IsFull())
	{
		TStack<T> st(2*Size);
		for (int i=0;i<Top+1;i++)
			st.pStack[i]=pStack[i];

		delete []pStack;
		Size=2*Size;
		pStack= new T[Size];
		
		for (int i=0;i<Top+1;i++)
			pStack[i]=st.pStack[i];
 	}

	Top++;
	pStack[Top]=elem;
	
}

//--------------------------------------------------------

template <class T>
bool TStack<T>::operator==(const TStack<T> &st) const
{
	
		if ((Size==st.Size)&&(Top==st.Top))
	{
			for (int i=0;i<Top+1;i++)
			{
				if (pStack[i]!=st.pStack[i])
					return false;
			}
			return true;
	}
	else
		return false;
}

//--------------------------------------------------------

template <class T>
TStack<T> &TStack<T>::operator=(const TStack &st)
{
	if (Size!=st.Size)
	{
		delete [] pStack;
		pStack= new T[st.Size];
	}
	Size=st.Size;
	Top=st.Top;
	for(int i=0;i<Top+1;i++)
		pStack[i]=st.pStack[i];
}

//--------------------------------------------------------

template <class T>
bool TStack<T>::IsEmpty()
{
	if (Top==-1)
		return true;
	else
		return false;
}

//--------------------------------------------------------

template<class T>
bool TStack<T>::IsFull()
{
	if (Top==(Size-1))
		return true;
	else 
		return false;
}

//--------------------------------------------------------

template<class T>
int TStack<T>::NumEl()
{
	return Top+1;
}

//--------------------------------------------------------

template<class T>
void TStack<T>::Clear()
{
	Top=-1;
}

#endif