#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

  ifstream ifile (argv[1]);
  if (ifile.fail()){
    return 1;
  }
  int base;
  char x;
  string _code, _d, _n, temp;
  ifile >> base >> _d >> _n;

//The try block lets you enclose one or more statements
//that might throw an exception.
try{
    //checking for valid bases
    BigInt zero(0, base);
    BigInt dTemp3(_d, base);
    BigInt nTemp3(_n, base);

    //checking for div by 0
    BigInt dTemp1(_d, base);
    BigInt nTemp1(_n, base);
    dTemp1 /= nTemp1;

    //checking for negative exponent
    BigInt dTemp2(_d, base);
    BigInt nTemp2(_n, base);
    BigInt temp(base);
    if (dTemp2 < zero){
      temp = pow(nTemp2, dTemp2);
    }
}
//The catch block will 'catch' an exception thrown by a statement in the try block.
//Since our custom exceptions inherit from std::exception, we can
//catch them all with std::exception type like so.
catch(const exception& e){
    cout<<e.what()<<endl;//print the message of the exception defined in its "what" function.
    return -1;//end the program and return status != 0 to indicate that there is an error.
}


  BigInt d(_d, base);
  BigInt n(_n, base);
  BigInt result(1, base);

  cout << endl;
  while (ifile >> _code){
    BigInt secret_code(_code, base);
    result = modPow(secret_code, d, n);
    char x = char(result.to_int());
    cout << x;
  }
  cout << endl << endl;
  ifile.close();

	return 0;
}
