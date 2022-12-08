#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
      //array of unsigned long longs to store result
      unsigned long long w[5] = {0,0,0,0,0};
      
      for (int i = 1; i <= 5; i++)
      {
        int startIndex = k.length() - 6*i;
        std::cout << "start index: " << startIndex << std::endl;
        if(startIndex >= 0)
        {
          w[5 - i] = substringTranslate(k.substr(startIndex, 6));
        }
        else
        {
          w[5 - i] = substringTranslate(k.substr(0, 6 + startIndex));
        }
        
        
        if(startIndex <= 0)
        {
          break;
        }
      }
      
      // // debug
      // for(int i = 0 ; i < 5 ; i++)
      // {
      //   std::cout << "w[" << i << "]=" << w[i] << std::endl;
      // }
      // // end debug
      
      return (rValues[0]*w[0]+rValues[1]*w[1]+rValues[2]*w[2]+rValues[3]*w[3]+rValues[4]*w[4]);
      
      
    }
  
  
  	//will handle 6 letters or less
  	unsigned long long substringTranslate (const std::string& k) const
    { 
      // make a copy of k
      std::string kCopy = k;
      // std::cout << "substr: " << kCopy << std::endl;
      
      //if the string is shorter than 6
      //place zeros in leading positions
      if (kCopy.length() < 6)
      {

        int numZeros = 6 - kCopy.length();
        
        for (int i=0; i < numZeros; i++)
      	{
          kCopy.insert(kCopy.begin(), 'a');
      	}
      }
      
      // std::cout << "substr after padding: " << kCopy << std::endl;
      
      unsigned long long cChars[6];
      for(int i = 0 ; i < 6 ; i++)
      {
        // std::cout << "kCopy[" << i << "]=" << kCopy[i] << std::endl;
        cChars[i] = letterDigitToNumber(kCopy[i]);
        // std::cout << "cChars[" << i << "]=" << cChars[i] << std::endl;
      }
      
      
      
      //equation to convert from base 36 to decimal
      return cChars[5]+36*(cChars[4]+36*(cChars[3]+36*(cChars[2]+36*(cChars[1]+36*(cChars[0])))));

    }


    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      	// Add code here or delete this helper function if you do not want it
      	if(letter >= 'A' && letter <= 'Z')
        {
          return letter -'A';
        }
      
      	if(letter >= 'a' && letter <= 'z')
        {
          return letter - 'a';
        }
      
      	if(letter >= '0' && letter <= '9')
        {
          return 26 + letter - '0';
        }
      
      	return 0;
      
      
//       	//convert upper case to lower case first if needed
//       	if (letter >= 'A' || letter <= 'Z')
//         {
//           //add 32 to the ASCII value
//           letter = letter+32;
//         }
      
//       	//convert to integer value (a-z is 0-25 and digits 0-9 are 26-35) and return this value/index
      
//       	HASH_INDEX_T counter = 0;
      
//       	for (char i = 'a'; i <= 'z'; i++)
//         {
//           //go through looking for a match
          
//           //set character equal to the counter integer value
//           if (i == letter)
//           {
//             return counter;
//           }
//           counter++;
//         }
      
//       //counter start at 26
//       counter = 26;
//       //if hasn't returned then it is a digit not a letter 
//       for (char i = '0'; i <= '9'; i++)
//         {
//           //go through looking for a match
          
//           //set character equal to the counter integer value
//           if (i == letter)
//           {
//             return counter;
//           }
        
//           counter++;
//         }
      
//       return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
