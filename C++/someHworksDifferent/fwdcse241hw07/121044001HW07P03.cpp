#include "121044001HW07P03.h"
namespace ListMYK{
	template <class T>
	UniqueList<T>::UniqueList(int newCapacity):List<T>(newCapacity){
		//Left empty intentionally
	}
	template <class T>
	UniqueList<T>::UniqueList(const UniqueList<T>& other):List<T>(other){
		//Left empty intentionally
	}
	template <class T>
	bool UniqueList<T>::add(T element){
		if (this->sizeOfList()==this->getCapacity()){
			T* temp = this->arr;
			this->capacity*=2;
			this->arr = new T[this->getCapacity()];//checks if the capacity is enough
			for (int i = 0; i < this->sizeOfList(); ++i)
				this->at(i)=temp[i];
			delete [] temp;
		}
		for(int i=0;i<this->sizeOfList();i++)
			if(this->at(i)==element)
				return false;//Adds the element if the elements is not in the List
		this->arr[this->sizeOfList()]=element;
		this->size++;
		return true;
	}
	
	template <class T>
	List<T>& UniqueList<T>::operator +(List<T>& other){
		UniqueList<T> *sum = new UniqueList<T>(*this);
		*sum += other;//returns the sum of two Lists and returns a unique list reference
		return *sum;
	}
	template <class T>
	List<T>& UniqueList<T>::operator %(List<T>& other){
		UniqueList<T> *sum = new UniqueList<T>(this->getCapacity());
		for(int i=0;i<this->sizeOfList();i++)//finds the common elements of two list
			if(other.find(this->at(i))>=0)//returns a unique list with that elements
				sum->add(this->at(i));
		return *sum;
	}
	template <class T>
	List<T>& UniqueList<T>::operator =(List<T>& other){
		if (other.getCapacity()!=this->getCapacity()){
			delete [] this->arr;
			this->capacity=other.getCapacity();
			this->arr = new T[this->getCapacity()];
		}
		this->size=0;//makes assignment
		for(int i=0;i<other.sizeOfList();i++)
			this->add(other.at(i));
		return *this;
	}


}