#include <iostream>
extern int calculate(std::string nameFile);
int main(int argc, char **argv){
	int result = calculate("file1.txt");
	if(result==0){
		std::cout << "Success!" << std::endl;
	} else {
		std::cout << "Failed!" << std::endl;
	}
	return 0;
}
