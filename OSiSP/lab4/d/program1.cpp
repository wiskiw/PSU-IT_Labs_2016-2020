#include <iostream>
extern int hello(std::string nameFile);
int main(int argc, char **argv){
	int result = hello("file1.txt");
	if(result==0){
		std::cout << "Success!" << std::endl;
	} else {
		std::cout << "Failed!" << std::endl;
	}
	return 0;
}
