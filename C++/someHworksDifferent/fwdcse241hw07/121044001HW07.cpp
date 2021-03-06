#include "121044001HW07P01.cpp"
#include "121044001HW07P03.cpp"
#include "121044001HW07P02.cpp"
using namespace ListMYK;
int main(){
	UniqueList<int> a(10);
	SortedList<int> b(5);

	try{
		UniqueList<int > c(-5);
	}
	catch(char const* errorMessage){
		cout << "exception handled the error message says: \"" << errorMessage << "\"" << endl; 
	}

	cout << "Testing add() function on UniqueList<int>" << endl;
	a.add(3);
	a.add(5);
	a.add(5);
	a.add(7);
	a.add(2);
	cout << a << endl;

	cout << "Testing add() function on SortedList<int>" << endl;
	b.add(3);
	b.add(5);
	b.add(1);
	b.add(7);
	b.add(2);
	cout << b << endl;
	cout << "Testing operator += on SortedList<int>" << endl;
	b+=a;
	cout << b << endl;
	cout << "Testing operator += on UniqueList<int>" << endl;
	a+=b;
	cout << a << endl;
	cout << "Testing remove() function on UniqueList<int>" << endl;
	a.remove(3);
	cout << a << endl;
	cout << "Testing operator % and operator = on SortedList<int>" << endl;
	b = b%a;
	cout << b << endl;
	cout << "Testing operator % and operator = on UniqueList<int>" << endl;
	a= a%b;
	cout << b << endl;
	cout << "Testing remove() function on SortedList<int>" << endl;
	b.remove(7);
	cout << b << endl;
	cout << "Testing operator + and operator = on UniqueList<int>" << endl;
	a=a+b;
	cout << a << endl;
}
