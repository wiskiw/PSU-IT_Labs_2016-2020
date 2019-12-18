//Вычислить сумму ряда ln(n)/n! с позиции N до позиции M. 
//Функцию вычисления суммы реализовать рекурсивно.
//Работу рекурсивной функции продемонстрировать в функции main. 
//Программу реализовать в диалоговом режиме: запрос данных - вывод ответа. 
//После каждого вывода ответа запрашивать у пользователя выход и, в случае положительного ответа, осуществлять завершение программы.

#include <iostream>
#include <cmath>

// Функцию факториала вынес в отдельную. Получилось 2 рекурсивные функции

using namespace std; 

int fakt(int);
double sum(int, int);
double result = 0;

int main(){
	setlocale(LC_ALL, "Russian");
	int begin;
	do{				
		int n, m;
		cout<<"Введите целое число - начальную позицию вычисления суммы\n";
		if( 1 != scanf( "%d", &n ) ){
		cout << "Некорректный ввод\n";
			break;  
		}
		cout<<"Введите целое число - конечную позицию вычисления суммы (больше начального)\n";
		if( 1 != scanf( "%d", &m ) ){
		cout << "Некорректный ввод\n";
			break;  
		}
		
		result = 0;
		double res;
		res = sum(n, m);
		
		cout<<"Сумма от n до m = "<<res;
		
		cout<<"\nЕсли хотите продолжить, нажмите 1.\nЕсли хотите выйти, нажмите 0.\n";
		cin>>begin;
		if( begin != 0 && begin != 1 ){
			cout<<"Некорректный ввод";
			break;
		}
	}
	while(begin);
}
double sum(int n, int m){
	if(n == m+1) return 1;
	sum(n+1, m);
	result += log(n)/fakt(n);
	//cout<<" логарифм = "<<log(n)<<" факториал = "<<fakt(n)<<"\n";
	return result;
}
int fakt(int n){
	int result;
	if (n == 1 || n == 0){
		return 1;
	}
	result = n * fakt(n - 1);
	return result;
}
