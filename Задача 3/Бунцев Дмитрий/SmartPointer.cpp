#include <iostream> 
#include <string> 
#include <conio.h> 

using namespace std;

template<class T>
class SmartPointer {


private:
	T* instance;
	int * counter;

public:
	SmartPointer() : instance(), counter() {
	}

	SmartPointer(T* instance) {
		this->instance = instance;
		counter = new int(1);
	}

	SmartPointer(const SmartPointer& pointer) : instance(pointer.instance), counter(pointer.counter) {
		if (counter) {
			++*counter;
		}
	}

	~SmartPointer() {
		release();
	}

	void release() {
		if (counter) {
			if (--*counter == 0) {
				delete counter;
				delete instance;
			}
		}

		counter = NULL;
		instance = NULL;
	}



	void Set(T* PointerObj) {
		release();
		counter = new size_t(1);
		instance = PoinerObj;
	}

	T* get() const {
		return counter ? instance : NULL;
	}

	SmartPointer& operator = (const SmartPointer& pointer) {
		if (this != &pointer) {
			release();
			instance = pointer.instance;
			counter = pointer.counter;
			if (counter) {
				++*counter;
			}
		}

		return *this;
	}

	T* operator -> () const {
		if (instance == nullptr) throw exception("Pointer deleted");
		return get();
	}

	T& operator * () const {
		return *get();
	}

	int getPointersCount() {
		return counter ? *counter : -1;
	}

};




int main(int argc, const char * argv[]) {



	SmartPointer<int> pointer(new int(2048));
	cout « pointer.get() « endl;
	auto pointer1 = pointer;
	cout « pointer1.get() « endl;
	SmartPointer<int> pointer2(pointer);
	cout « pointer2.get() « endl;
	SmartPointer<int> pointer3(new int(175));
	cout« pointer3.get() « endl;
	pointer.release();
	cout « pointer1.get() « " " « pointer3.get() « endl;

	return 0;
}