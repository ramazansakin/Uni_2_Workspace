#ifndef LIST_H
#define LIST_H 
#include <iostream>
namespace ListMYK{
	template <class T>
	class List
	{
	public:
		List(int newCapacity);//gets capacity and makes a list with that capacity
		List(const List<T>& other);//copy constructer
		virtual bool add(T element)=0;//adds element (pure virtual) 
		// it is pure virtual because it can be changeable for the derived classes
		
		bool remove(T element);//removes the given element
		int find(T element);//returns the index of given element
		int sizeOfList();//returns the size of list
		int getCapacity();//returns capacity
		T& at(int index);//returns the reference of the element in given index
		List<T>& operator +=(List<T>& other);//adds alist to another (pure virtual) 
		virtual List<T>& operator +(List<T>& other)=0;//returns a reference to a list which is addition of two lists (pure virtual)
		virtual List<T>& operator %(List<T>& other)=0;//returns a reference to a list with common elements of two lists (pure virtual)
		virtual List<T>& operator =(List<T>& other)=0;//assigns right side to left side (pure virtual)
		~List();
	protected:
		T* arr;
		int size;
		int capacity;
	};
}
#endif
