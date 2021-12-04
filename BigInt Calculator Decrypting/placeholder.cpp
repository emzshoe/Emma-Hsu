// now, a and b will have the same sign
   // case 3, both positive
  int aVal, bVal, borrow = 0, smallDiff;
  if (isPositive && b.isPositive){
    if (*this > b){
      // a is the larger positive number
      for (unsigned int i = 0; i < vec.size(); i++){
        // getting the values for each digit place
        aVal = vec[i];
        if (i > (b.vec).size()){
          bVal = 0;
        } else {
          bVal = (b.vec)[i];
        }
        
        //perform arithmetic then add to temp vector
        smallDiff = aVal - borrow - bVal;
        if (smallDiff >= 0){
          temp.push_back(smallDiff);
        } else if (smallDiff < 0){
          borrow = 1;
          smallDiff += base;
          temp.push_back(smallDiff);
        }
      }
      this -> vec = temp;
    } else { // this < b
      // dont need >= or <= since that was the base case
      // b is the larger positive number
      for (unsigned int i = 0; i < (b.vec).size(); i++){
        bVal = (b.vec)[i];
        if (i > vec.size()){
          aVal = 0;
        } else{
          aVal = vec[i];
        }
        
        // performing arithmetic then append to temp vector
        smallDiff = bVal - borrow - aVal;
        if (smallDiff >= 0){
          temp.push_back(smallDiff);
        } else if (smallDiff < 0){
          borrow = 1;
          smallDiff += base;
          temp.push_back(smallDiff);
        }
      }
      this -> vec = temp;
      this -> isPositive = false;
    }
  }
  
  // case 4, both negative
  else {
    if (*this > b){
      for (unsigned int i = 0; i < (b.vec).size(); i++){
        bVal = (b.vec)[i];
        if (i > vec.size()){
          aVal = 0;
        } else{
          aVal = vec[i];
        }
        
        // performing arithmetic then append to temp vector
        smallDiff = bVal - borrow - aVal;
        if (smallDiff >= 0){
          temp.push_back(smallDiff);
        } else if (smallDiff < 0){
          borrow = 1;
          smallDiff += base;
          temp.push_back(smallDiff);
        }
      }
      this -> vec = temp;
      this -> isPositive = true;
    } else { // this < b
      for (unsigned int i = 0; i < vec.size(); i++){
        // getting the values for each digit place
        aVal = vec[i];
        if (i > (b.vec).size()){
          bVal = 0;
        } else {
          bVal = (b.vec)[i];
        }
        
        //perform arithmetic then add to temp vector
        smallDiff = aVal - borrow - bVal;
        if (smallDiff >= 0){
          temp.push_back(smallDiff);
        } else if (smallDiff < 0){
          borrow = 1;
          smallDiff += base;
          temp.push_back(smallDiff);
        }
      }
      this -> vec = temp;
      this -> isPositive = false;
    }
  }




    do {
      //count how many times the divisor is in the dividend
      int times = 0;
      while (dividend_seq >= positive_divisor){
        dividend_seq -= positive_divisor;
        times++;
      }
      cout << "times: " << times << endl;
      
      //push back on quotient
      quotient.vec.push_back(times);
      if(dividend_seq.to_int() == 0){
        dividend_seq.vec.clear();
      }
      
      //pull down more digits
      BigInt temp(base);
      temp.vec.push_back(vec[position - 1]);
      for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        temp.vec.push_back((dividend_seq.vec)[i]);
      }
      
      position--;
    } while (position >= 0);
    
    if (vec.size() == 0){
      BigInt zero(0, base);
      remainder = zero;
    } else {
      remainder = dividend_seq;
    }
   
// 11/24 2:55 pm placeholder
//      //counting how many times i can subtract the divisor from divident_seq
//      //loop here for (i )
//      while (position >= 0){
//     int times = 0;
//     while (dividend_seq >= positive_divisor){
//       dividend_seq -= positive_divisor;
//       times++;
//       //cout << "times: " << times << endl;
//     }
    
//     //append times to quotient
//     quotient.vec.push_back(times);
//     if (dividend_seq.to_int() == 0){
//       dividend_seq.vec.clear();
//     }
    
//     //pulling down more digits if there are more digits to pull down
//     if (position >= 1){
//       BigInt temp(base);
//       position--;
//       temp.vec.push_back(vec[position]);
//       for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
//         temp.vec.push_back((dividend_seq.vec)[i]);
//       }
//       dividend_seq = temp;
//     }
//     }
//     remainder = dividend_seq;


//11/25/1:54
//   if ((this -> vec) > b.vec){
//     cout << "hello" << endl;
//     quotient.vec = zero.vec;
//     quotient.isPositive = true;
//   }
  
  
//   if (tempDivisor.to_int() > tempDividend.to_int()){
//       cout <<"enters division" <<endl;

//     //BigInt zero(0, base);
//     quotient.vec = zero.vec;
//     quotient.isPositive = true;
//   }



  //long division
  else {
    remainder.isPositive = this -> isPositive;
    if ((isPositive && b.isPositive) || (!isPositive && !(b.isPositive))) {
      quotient.isPositive = true;
      //remainder.isPositive = true;
    } else {
      quotient.isPositive = false;
      //remainder.isPositive = false;
    }
    //finding the shortest sequence of digits starting from the leftmost digit
    int position = vec.size() - 1;
    BigInt dividend_seq(vec[position], base);
    BigInt positive_divisor(base);
    positive_divisor = b;
    positive_divisor.isPositive = true;
    while (dividend_seq < positive_divisor){
      BigInt temp(base);
      position--;
      temp.vec.push_back(vec[position]);
      for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        temp.vec.push_back((dividend_seq.vec)[i]);
      }
      dividend_seq = temp;
    }
    while (position >= 0){  
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
    
      //pulling down more digits if there are more digits to pull down
      BigInt temp(base);
      position--;
      temp.vec.push_back(vec[position]);
      for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        temp.vec.push_back((dividend_seq.vec)[i]);
      }
      dividend_seq = temp;
    }
    //flip quotient
    BigInt temp(base);
    temp = quotient;
    for (unsigned int i = 0; i < quotient.vec.size(); i++){
      (quotient.vec)[i] = (temp.vec)[quotient.vec.size() - i - 1];
    }
    //printing DELETE
    for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
        //cout << "dividend_seq[" << i << "] = " << (dividend_seq.vec)[i] << endl;
    }
    
    //remainder for long division
    //remove leading zeros by first flipping dividend_seq then popping the back if = 0
    BigInt remTemp(base);
    int sigIndex = 0;
    for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
      remTemp.vec.push_back((dividend_seq.vec)[(dividend_seq.vec.size())- i - 1]);
    }
    for (unsigned int i = 0; i < dividend_seq.vec.size(); i++){
      if ((remTemp.vec)[i] != 0){
        sigIndex = i;
      }
    }
    for (int i = remTemp.vec.size() - 1; i > sigIndex; i--){
      remTemp.vec.pop_back();
    }
    for (unsigned int i = 0; i < remTemp.vec.size(); i++){
      remainder.vec.push_back((remTemp.vec)[remTemp.vec.size() - i - 1]);
    }
    
    if (remainder.to_int() == 0){
      remainder.isPositive = true;
    }
    
  }