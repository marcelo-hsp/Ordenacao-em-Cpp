#include <iostream>
#include <thread>
#include <vector>


void foo()
{
	std::cout << "foo" << std::endl;
}


int main()
{
	std::thread t1(foo);

	return 0;
}