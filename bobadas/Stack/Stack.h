#ifndef STACK_H_
#define STACK_H_

#include <string>
#include <ostream>

typedef unsigned int Nat;

template <typename T>
class Stack{
	private:
	
		struct StackElem{
			T dato;
			StackElem *sig;
		};
	
	StackElem* top;
	Nat tam;
	
	
	public:
		Stack();
		~Stack();
		void Push(const T& elem);
		const T& Pop(); //saca de la pila y retorna el elemento
		void Show();
		const Nat cantElem();
};

template <typename T>
Stack::Stack()
	: top(nullptr), tam(0) {
}

template <typename T>
Stack::~Stack(){
	while(cantElem() > 0){
		Pop();
	}
}

template <typename T>
void Stack::Push(const T& elem){
	StackElem* nuevo= new StackElem;
	nuevo->dato = elem;
	nuevo->sig = top;
	top = nuevo;
	tam++;
}

template <typename T>
const T& Stack::Pop(){
	StackElem* old = top;
	res = old->dato;
	top = top->sig;
	tam--;
	delete old;
	return res;
}

template <typename T>
void Stack::Show(){}

template <typename T>
const Nat Stack::cantElem(){
	return tam;
}
#endif // STACK_H_
