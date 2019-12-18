#include <iostream>
extern int hello(std::string nameFile);
int main(int argc, char **argv){
	int result = hello("1.txt");
	if(result==0){
		std::cout << "Success!" << std::endl;
	} else {
		std::cout << "Failed!" << std::endl;
	}
	return 0;
}
