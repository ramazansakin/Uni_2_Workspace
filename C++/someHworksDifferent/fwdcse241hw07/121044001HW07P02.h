#ifndef SORTEDLIST_H
#define SORTEDLIST_H 
#include "121044001HW07P01.h"
namespace ListMYK{
	template <class T>
	class SortedList :public List<T>//derives from List class
	{
	public:
		SortedList(int newCapacity);//gets capacity and makes a list with that capacity
		SortedList(const SortedList<T>& other);//copy constructer
		bool add(T element);//adds element
		List<T>& operator +(List<T>& other);//returns a sorted list of addition of two lists
		List<T>& operator %(List<T>& other);//returns a sorted list with common elements of two lists
		List<T>& operator =(List<T>& other);//assigns right side to left side
		/*
		Functions that is inherited from List class look List.h for more information
		bool remove(T element);
		int find(T element);
		int sizeOfList();
		int getCapacity();
		T& at(int index);
		List<T>& operator +=(List<T>& other);
		*/

	};
}
#endif