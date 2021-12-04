#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

/*
Create a default BigInt with base 10.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
Create a BigInt with a specified base.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    int num = input;
    isPositive = true;
    if (input < 0){
      num *= -1;
      isPositive = false;
    }

    while (num > 0){
      vec.push_back(num % base);
      num /= base;
    }
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
  base = setbase;
  isPositive = true;
  for (int i = s.length() - 1; i >= 0; i--){
    int x = int(s[i]);
    if (x == 45){
      isPositive = false;
    } else if (x >= 65){
      vec.push_back(int(s[i] - 55));
    } else {
      vec.push_back(int(s[i] - 48));
    }
  }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){
  *this = b;

}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){
    /************* You complete *************/
  this -> vec = b.vec;
  this -> base = b.base;
  this -> isPositive  = b.isPositive;
  return *this;
}

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){
  string s = "";
  if (vec.size() == 0){
    return "0";
  }
  if (!isPositive){
    s += "-";
  }
  for (int i = vec.size() - 1; i >= 0; i--){
    if (vec[i] < 10){
      s += char(vec[i] + 48);
    } else {
      s += char(vec[i] + 55);
    }
  }
  return s;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{
  int sum = 0;
  for (unsigned int i = 0; i < vec.size(); i++){
    sum += vec[i] * pow(base, i);
    if (!isPositive){
      if (-sum >= INT_MAX){
        return INT_MIN;
      }
    } else if (sum <= INT_MIN){
      return INT_MAX;
    }
  }
  if (isPositive){
    return sum;
  }
  return -1 * sum;
}

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
  int a = vec.size();
  int c = (b.vec).size();

  //first positive, other negative
  if (isPositive && !b.isPositive){
    return 1;
  //first negative, other positive
  } else if (!isPositive && b.isPositive){
    return -1;
  //both positive
  } else {
    //multiplying ending factor depending if they're both pos or neg
    int n = 1;
    if (!isPositive){
      n = -1;
    }
    if (a > c){
      return  n * 1;
    } else if (a < c){
      return n * -1;
    } else{
      //both vectors are positive of the same length
      for (int i = vec.size() - 1; i >= 0; i--){
        if (vec[i] > (b.vec)[i]){
          return n * 1;
        } else if (vec[i] < (b.vec)[i]){
          return n * -1;
        }
      }
    }
  }
  return 0;
}

//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x == 0){
    return true;
  }
  return false;
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x != 0){
    return true;
  }
  return false;
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x == 0 || x == -1){
    return true;
  }
  return false;
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x == 0 || x == 1){
    return true;
  }
  return false;
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x == 1){
    return true;
  }
  return false;
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  int x = a.compare(b);
  if (x == -1){
    return true;
  }
  return false;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){
  BigInt temp = a;
	temp += b;
  return temp;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
  vector<int> temp;
	//base case: adding additive identity
	if (vec == b.vec && (isPositive ^ b.isPositive)){
		temp.push_back(0);
    this -> vec = temp;
    this -> isPositive = true;
		return *this;
	}
  int aVal, bVal, carry = 0, smallSum, digit;
  //a and b have the same sign
  if (isPositive == b.isPositive){
    for (unsigned int i = 0; i < max(vec.size(), (b.vec).size()); i++){
      if (i < vec.size()){
        aVal = vec[i];
      } else {
        aVal = 0;
      }
      if (i < (b.vec).size()){
        bVal = (b.vec)[i];
      } else {
        bVal = 0;
      }
      //adding aVal and bVal
      smallSum = aVal + bVal + carry;
      carry = smallSum / base;
      digit = smallSum % base;
      temp.push_back(digit);
    }
    if (carry != 0){
      temp.push_back(carry);
    }
    // vector of a now points to this new vector
    this -> vec = temp;
  } else if (isPositive && !(b.isPositive)) {
    // a is positive, b is negative
    // subtract b from a, point 'this' to a
    BigInt tempNum = b;
    tempNum.isPositive = true;
    *this -= tempNum;
  } else if (!isPositive && b.isPositive) {
    // a is negative, b is positive
    // subtract a from b, point 'this' to b
    this -> isPositive = true;
    if (*this < b){
      *this -= b;
      this -> isPositive = true;
    } else { //*this > b
      *this -= b;
      this -> isPositive = false;
    }
  }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){
  BigInt temp = a;
	temp -= b;
  return temp;
}

/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
  vector<int> temp;
  // case 1, subtracting by itself
  if (*this == b){
    temp.push_back(0);
    this -> vec = temp;
    this -> isPositive = true;
		return *this;
  }
  // case 2, if a and b have different signs, invoke +=
  else if (!isPositive && b.isPositive) {
    // invoking += operator
    this -> isPositive = true;
    *this += b;
    this -> isPositive = false;
    return *this;
  } else if (isPositive && !(b.isPositive)){
    // invoking += operator
    this -> isPositive = false;
    *this += b;
    this -> isPositive = true;
    return *this;
  }
  // case 3, both numbers are positive
  else if (isPositive && b.isPositive){
    int aVal, bVal, borrow = 0, diff;
    if (*this > b){
      for (unsigned int i = 0; i < vec.size(); i++){
        //assigning value to each digit to be manipulated
        aVal = vec[i];
        if (i < (b.vec).size()){
          bVal = (b.vec)[i];
        } else {
          bVal = 0;
        }
        //manipulating digits
        diff = aVal - borrow - bVal;
        if (diff >= 0){
          borrow = 0;
        }
        if (diff < 0){
          diff += base;
          borrow = 1;
        }
        temp.push_back(diff);
      }
      this -> vec = temp;
    } else {
      for (unsigned int i = 0; i < (b.vec).size(); i++){
        //assigning value to each digit to be manipulated
        bVal = (b.vec)[i];
        if (i < vec.size()){
          aVal = vec[i];
        } else {
          aVal = 0;
        }
        //manipulating digits
        diff = bVal - borrow - aVal;
        if (diff >= 0){
          borrow = 0;
        }
        if (diff < 0){
          diff += base;
          borrow = 1;
        }
        temp.push_back(diff);
      }
      this -> vec = temp;
      this -> isPositive = false;
    }
  }
  // case 4, both numbers are negative
  else {
  int aVal, bVal, borrow = 0, diff;
    if (*this > b){
    for (unsigned int i = 0; i < (b.vec).size(); i++){
        //assigning value to each digit to be manipulated
        bVal = (b.vec)[i];
        if (i < vec.size()){
          aVal = vec[i];
        } else {
          aVal = 0;
        }
        //manipulating digits
        diff = bVal - borrow - aVal;
        if (diff >= 0){
          borrow = 0;
        }
        if (diff < 0){
          diff += base;
          borrow = 1;
        }
        temp.push_back(diff);
      }
      this -> vec = temp;
      this -> isPositive = true;
    } else { // *this < b
      for (unsigned int i = 0; i < vec.size(); i++){
        //assigning value to each digit to be manipulated
        aVal = vec[i];
        if (i < (b.vec).size()){
          bVal = (b.vec)[i];
        } else {
          bVal = 0;
        }
        //manipulating digits
        diff = aVal - borrow - bVal;
        if (diff >= 0){
          borrow = 0;
        }
        if (diff < 0){
          diff += base;
          borrow = 1;
        }
        temp.push_back(diff);
      }
      this -> vec = temp;
    }
  }
  //removing leading 0s
  unsigned int sigIndex = 0;
  for (unsigned int i = 0; i < vec.size(); i++){
    if (vec[i] != 0){ //find the index of the front most significant digit
      sigIndex = i;
    }
  }
  for (unsigned int i = vec.size() - 1; i > sigIndex; i--){
    vec.pop_back(); // popping additional zeros from the back
  }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){
    /************* You complete *************/
  BigInt temp = a;
  temp *= b;
  return temp;
}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
  //1, base case, a or b is 0
  if (b.to_int() == 0){
    this -> vec = b.vec;
    this -> isPositive = true;
    return *this;
  } else if ((*this).to_int() == 0){
    this -> vec = vec;
    this -> isPositive = true;
    return *this;
  }

  //2, base case, a = 1, -1
  if ((*this).to_int() == 1){
    this -> vec = b.vec;
    this -> isPositive = b.isPositive;
    return *this;
  } else if ((*this).to_int() == -1){
    this -> vec = b.vec;
    this -> isPositive = !b.isPositive;
    return *this;
  }

  //3, long multiplication
  //assigning the sign of the final num
  if ((isPositive && b.isPositive) || (!isPositive && !(b.isPositive))) {
    this -> isPositive = true;
  } else {
    this -> isPositive = false;
  }

  //carrying out long multiplication
    BigInt total(0, base);
    int product;
    //looping through each digit in b
    for (unsigned int i = 0; i < (b.vec).size(); i++){
      BigInt temp(base);
      //adding additional zeros to the front
      for (unsigned int k = 0; k < i; k++){
        (temp.vec).push_back(0);
      }
      //reset the carry for each iterated digit in a
      int carry = 0;
      //looping through each digit in a
      for (unsigned int j = 0; j < vec.size(); j++){
        product = ((b.vec)[i] * vec[j]) + carry;
        if (product < base){
          carry = product / base;
          product = product % base;
        }
        (temp.vec).push_back(product);
      }
      //adding an additional carry digit
      if (carry != 0){
        (temp.vec).push_back(carry);
      }
      total += temp;
    }
  this -> vec = total.vec;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){
    /************* You complete *************/
  BigInt temp = a;
  temp /= b;
  return temp;
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
  //create two BigInts for the quotient and remainder
  BigInt quo(base), rem(base);
  //call divisionMain on BigInt a
  this -> divisionMain(b, quo, rem);
  *this = quo;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a;
    temp %= b;
    return temp;
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    //create two BigInts for the quotient and remainder
    BigInt quo(base), rem(base);
    //call divisionMain on BigInt a
    this -> divisionMain(b, quo, rem);
    *this = rem;
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){
  //creating two BigInts, one and zero
  BigInt zero(0, base);
  BigInt one(1, base);

  //creating temp numbers to compare the magnitudes
  BigInt temp(0, base);
  BigInt tempDividend(*this);
  BigInt tempDivisor(b);
  tempDividend.isPositive = true;
  tempDivisor.isPositive = true;

  //if the divisor is greater than the dividend
  if (tempDivisor > tempDividend){
    quotient = zero;
    remainder = *this;
  }

  //long division
  else {
    //signs for the quotient and remainder
    if ((isPositive && b.isPositive) || (!isPositive && !(b.isPositive))) {
      quotient.isPositive = true;
    } else {
      quotient.isPositive = false;
    }
    //finding the shortest sequence of digits starting from the leftmost digit
    int position = vec.size() - 1;
    BigInt dividend_seq(vec[position], base);
    BigInt positive_divisor(base);
    positive_divisor = b;
    positive_divisor.isPositive = true;
    while (dividend_seq < positive_divisor){
      position--;
      temp.vec.push_back(vec[position]);
      for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        temp.vec.push_back((dividend_seq.vec)[i]);
      }
      dividend_seq = temp;
      temp.vec.clear();
    }
    while (position > 0){
      int times = 0;
      while (dividend_seq >= positive_divisor){
        dividend_seq -= positive_divisor;
        times++;
      }
      //append times to quotient
      quotient.vec.push_back(times);
      if (dividend_seq.to_int() == 0){
        dividend_seq.vec.clear();
      }

      position--;
      temp.vec.push_back(vec[position]);
      for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        temp.vec.push_back((dividend_seq.vec)[i]);
      }
      dividend_seq = temp;
      temp.vec.clear();
    }

    //when position = 0
    int times = 0;
    while (dividend_seq >= positive_divisor){
      dividend_seq -= positive_divisor;
      times++;
    }
    //append times to quotient
    quotient.vec.push_back(times);
    temp.vec.push_back(vec[0]);
    for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
      temp.vec.push_back((dividend_seq.vec)[i]);
    }
    dividend_seq = temp;
    temp.vec.clear();
    // end of when position = 0

    //flip quotient
    temp = quotient;
    for (unsigned int i = 0; i < quotient.vec.size(); i++){
      (quotient.vec)[i] = (temp.vec)[quotient.vec.size() - i - 1];
    }
    temp.vec.clear();

    //remainder for long division
    remainder = dividend_seq;
    remainder.vec.erase(remainder.vec.begin());
    remainder.isPositive = this -> isPositive;
    if (remainder.vec.size() == 1 && remainder.vec[0] == 0){
      remainder.isPositive = true;
    }
  }
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){
    /************* You complete *************/
    BigInt temp = a;
    temp.exponentiation(b);
    return temp;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
  //base case, power is 0
    BigInt zero(0, base);
    BigInt one(1, base);
    BigInt two(2, base);
    BigInt exp(base);
    exp = b;
    if (b.to_int() == 0){
      *this = one;
    } else if (this -> to_int() == 0){
      *this = zero;
    } else { //all other powers
      BigInt result(1, base);
      BigInt bae(this -> to_int(), base);
      while(exp.to_int() > 1){
        if (exp.to_int() % 2 == 1){ //if exponent is odd: 3, 5, 7, 9...
          //subtract power by one
          exp -= one;
          result *= bae;
        } else { //exponent is even: 2, 4, 6, 8...
          bae *= bae;
          exp /= two;
        }
      }
      result *= bae;
      *this = result;
    }
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
    BigInt temp = a;
    temp.modulusExp(b, m);
    return temp;
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    BigInt one(1, base);
    BigInt two(2, base);
    BigInt exp(base);
    exp = b;
    BigInt result(1, base);
    //BigInt bae(this -> to_int(), base);
    while (exp > one){
      if(exp % two == one) { //exponent is 3, 5, 7, 9...
        result = (result * (*this)) % m;
        exp -= one;
      } else { //exponent is 2, 4, 6, 8...
        *this = (*this * *this) % m;
        exp /= two;
      }
    }
    *this = (result * *this) % m;
    return *this;
}
