#include <iostream>
#include "Stack.h"
int main(){
	Stack< int > s;
	
	s.Push(8);
	s.Push(9);
	s.Push(42);
	s.Push(64);
	
	int n = s.Pop();
	
	std::cout << n << "\n";
	
	return 0;
}
