#include "bigint.cpp"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
  BigInt a(-1,10);
	cout << "a val: " << a.to_int() << endl;
  BigInt b(-1, 10);
	cout << "b val: " << b.to_int() << endl;
  BigInt c(7, 10);
	cout << "c val: " << c.to_int() << endl;
  
  BigInt k(10);
  a /= b;
  cout << "a /= b   " << a.to_int() << endl;
}