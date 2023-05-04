#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

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
        // 
      std::vector <std::string> a; 
      std::string reversed= std::string(k.rbegin(), k.rend());
      for (int i=4; i >= 0; i--){
        std::string partial="";
        if (i*6< reversed.size()){
          partial =reversed.substr(i*6, 6);
          

        }
        int count_fill= 6-partial.size();
        std::string empty_filled(count_fill, 'a');
        partial=partial+empty_filled;
        a.push_back(partial);

      }
      
      HASH_INDEX_T w[5];
      for (int i =0; i < 5;i++ ){
        w[i] = letterDigitToNumber(a[i][5]);
        for (int j=4; j >= 0; j--){
          w[i] *= 36;
         w[i] += letterDigitToNumber(a[i][j]);
        }
        // std::cout << w[i] << std::endl;
      }
      HASH_INDEX_T h=0;
      for (int i=0; i < 5; i++){
        h+=(rValues[i]*w[i]);
      }
      return h; 


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //std::string alpha="abcdefghijklmnopqrstuvwxyz";
        //std::string numeric="0123456789";
        char lower_case= tolower(letter);
        
        
        if (lower_case >= 'a' && lower_case <= 'z'){
          return static_cast<HASH_INDEX_T>(int(letter)-'a');
        }
        else if(lower_case >= '0' && lower_case <= '9'){
          return static_cast<HASH_INDEX_T>((letter)-48+26);
        }

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
