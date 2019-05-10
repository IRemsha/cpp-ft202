#include <iostream>
#include <string>
#include "Smart_ptr.h"

using namespace std;

int main() 
{
	auto ptr = smart_ptr<int>(new int(100500));
	cout << ptr.get() << "\n";
	
	auto ptr2 = ptr;
	cout << *ptr2 << "\n";

	auto ptr3 = smart_ptr<string>(new string("abcd"));
	cout << ptr3->length() << "\n";

	ptr2.release();
	cout << *ptr << "\n";
	return 0;
}