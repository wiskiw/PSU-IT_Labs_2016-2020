//��������� ����� ���� ln(n)/n! � ������� N �� ������� M. 
//������� ���������� ����� ����������� ����������.
//������ ����������� ������� ������������������ � ������� main. 
//��������� ����������� � ���������� ������: ������ ������ - ����� ������. 
//����� ������� ������ ������ ����������� � ������������ ����� �, � ������ �������������� ������, ������������ ���������� ���������.

#include <iostream>
#include <cmath>

// ������� ���������� ����� � ���������. ���������� 2 ����������� �������

using namespace std; 

int fakt(int);
double sum(int, int);
double result = 0;

int main(){
	setlocale(LC_ALL, "Russian");
	int begin;
	do{				
		int n, m;
		cout<<"������� ����� ����� - ��������� ������� ���������� �����\n";
		if( 1 != scanf( "%d", &n ) ){
		cout << "������������ ����\n";
			break;  
		}
		cout<<"������� ����� ����� - �������� ������� ���������� ����� (������ ����������)\n";
		if( 1 != scanf( "%d", &m ) ){
		cout << "������������ ����\n";
			break;  
		}
		
		result = 0;
		double res;
		res = sum(n, m);
		
		cout<<"����� �� n �� m = "<<res;
		
		cout<<"\n���� ������ ����������, ������� 1.\n���� ������ �����, ������� 0.\n";
		cin>>begin;
		if( begin != 0 && begin != 1 ){
			cout<<"������������ ����";
			break;
		}
	}
	while(begin);
}
double sum(int n, int m){
	if(n == m+1) return 1;
	sum(n+1, m);
	result += log(n)/fakt(n);
	//cout<<" �������� = "<<log(n)<<" ��������� = "<<fakt(n)<<"\n";
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
