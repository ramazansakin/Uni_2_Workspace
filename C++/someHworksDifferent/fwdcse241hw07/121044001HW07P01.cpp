#include "121044001HW07P01.h"
using namespace std;
namespace ListMYK{
	template <class T>
	List<T>::List(int newCapacity):capacity(newCapacity),size(0){
		if (capacity<0)//if the capacity is below 0 throws an exception
			throw "Capacity can't be below 0";
		arr = new T[capacity];
	}
	template <class T>
	List<T>::List(const List& other):capacity(other.capacity),size(other.size){
		arr = new T[capacity];//copy constructer
		for(int i=0;i<size;i++)
			arr[i]=other.arr[i];
	}
	template <class T>
	bool List<T>::remove(T element){
		for(int i=0;i<size;i++)
			if(element==arr[i]){//removes the given element
				for(int j=i;j<size-1;j++)
					arr[j]=arr[j+1];
				size--;
				return true;
			}
		return false;
	}
	template <class T>
	int List<T>::find(T element){
		for(int i=0;i<size;i++)//retruns the index of given element
			if(element==arr[i])//if there is not such an element 
				return i;		//returns -1
		return -1;
	}
	template <class T>
	int List<T>::sizeOfList(){
		return size;//returns size of the list
	}
	template <class T>
	int List<T>::getCapacity(){
		return capacity;//returns capacity
	}
	template <class T>
	T& List<T>::at(int index){
		if(index>=size){//returns the reference in the given index
			T *i=NULL;
			return *i;
		}
		return arr[index];
	}
	template <class T>
	ostream& operator <<(ostream& out, List<T>& other){
		for(int i=0;i<other.sizeOfList();i++)
			out << other.at(i) << " ";//prints every element to the stream
		return out; 
	}
	template <class T>
	List<T>& List<T>::operator +=(List<T>& other){//adds the right side to left side
		if (this->sizeOfList()+other.sizeOfList()>this->getCapacity()){
			T* temp = this->arr;
			this->capacity=this->getCapacity()+other.getCapacity();
			this->arr = new T[this->getCapacity()];
			for (int i = 0; i < this->sizeOfList(); ++i)
				this->arr[i]=temp[i];
			delete [] temp;
		}
		for(int i=0;i<other.sizeOfList();i++)
			this->add(other.at(i));
		
		return *this;
	}

	template <class T>
	List<T>::~List(){
		delete [] arr;//deletes tooken array from hype
	}
}
