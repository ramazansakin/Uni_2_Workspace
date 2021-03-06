#include "121044001HW07P02.h"
namespace ListMYK{
	template <class T>
	SortedList<T>::SortedList(int newCapacity):List<T>(newCapacity){
		//Left empty intentionally
	}
	template <class T>
	SortedList<T>::SortedList(const SortedList<T>& other):List<T>(other){
		//Left empty intentionally
	}
	template <class T>
	bool SortedList<T>::add(T element){
		if (this->sizeOfList()==this->getCapacity()){
			T* temp = this->arr;
			this->capacity*=2;
			this->arr = new T[this->getCapacity()];//checks if the capacity is enough
			for (int i = 0; i < this->sizeOfList(); ++i)
				this->arr[i]=temp[i];
			delete [] temp;
		}
		for(int i=0;i<=this->sizeOfList();i++){
			if(element<this->arr[i]||i==this->sizeOfList()){
				for(int j=this->sizeOfList()-1;j>=i;j--)//finds the place of element and puts it there
					this->arr[j+1]=this->arr[j];
				this->arr[i]=element;
				this->size++;
				return true;
			}
		}
		return false;
	}
	
	template <class T>
	List<T>& SortedList<T>::operator +(List<T>& other){
		SortedList<T> *sum = new SortedList<T>(*this);
		*sum += other;//returns the sum of two Lists and returns a sorted list reference
		return *sum;
	}
	
	template <class T>
	List<T>& SortedList<T>::operator %(List<T>& other){
		SortedList<T> *sum = new SortedList<T>(this->getCapacity());
		for(int i=0;i<this->sizeOfList();i++)//finds the common elements of two list
			if(other.find(this->arr[i])>=0)//returns a sorted list with that elements
				sum->add(this->arr[i]);
		return *sum;
	}
	template <class T>
	List<T>& SortedList<T>::operator =(List<T>& other){
		if (other.getCapacity()!=this->getCapacity()){
			delete [] this->arr;
			this->capacity=other.getCapacity();//makes assignment
			this->arr = new T[this->getCapacity()];
		}
		
		this->size=0;
		for(int i=0;i<other.sizeOfList();i++)
			this->add(other.at(i));
		return *this;
	}


}
