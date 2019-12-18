#include <iostream>
// g++ -std=c++11 Dprogram1.cpp -L/lib/ -ldynamic -o a3.out
extern int hello(std::string nameFile);
int main(int argc, char **argv){
	int x = hello("1.txt");
	std::cout << "Return code: " << x << std::endl;
	return 0;
}
