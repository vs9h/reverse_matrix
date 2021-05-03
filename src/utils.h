#pragma once

#include <string>
#include <boost/algorithm/string.hpp> // find ?
#include "complex.h"

double strtod(const std::string& str){
    double temp = 0;
    auto it = str.begin();
    bool is_positive = true;
    if (*it == '-'){
        is_positive = false;
        it++;
    } else if (*it == '+'){
        is_positive = true;
        it++;
    }
    while (it!=str.end() && *it!='.')
        temp=temp*10+(int(*(it++))-'0');
    if (it++ == str.end()){   
        if (!is_positive) temp*=-1;
        return temp;}
    double graduation = 0.1;
    while (it!=str.end()){
        temp = temp + graduation *(int(*(it++))-'0');
        graduation*=0.1;
    }
    if (!is_positive) temp*=-1;
    return temp;
}

// string to C, input string example: "+1+8i", "-9i", "+1i", "-1i";
C strtoc(const std::string& str){
    auto it = str.begin();
    auto prev_it = it;
    if (str[str.size()-1] != 'i') return C(strtod(str)); // if complex number has only real part (~real number)
    int sign_count = 0;
    for (size_t i = 0; i<str.size(); ++i)
        if (str[i]=='-' || str[i]=='+')
            sign_count++;
    if (sign_count == 1) // only imaginary part;
        return C(0,strtod(str.substr(0,str.size()-1)));

    // complex number has a real part and imaginary part;
    auto find_second_sign = std::find(str.begin()+1, str.end(), '+');
    if (find_second_sign == str.end())
        find_second_sign = std::find(str.begin()+1, str.end(), '-');
    size_t first_part_end = std::min(str.find('+', 1), str.find('-',1));
    return C(strtod(str.substr(0, first_part_end)), strtod(str.substr(first_part_end, str.length()-first_part_end-1)));
}

// this funcition shows how operator<< works in class 'C'
// You can use this function in main() function to check.
void test_C_output(){
    std::vector<C> numbers;
    numbers.push_back({0,1});
    numbers.push_back({1,-1});
    numbers.push_back({1,0});
    numbers.push_back({1,1});
    numbers.push_back({0,-1});
    numbers.push_back({1,0});
    numbers.push_back({-1,-1});
    numbers.push_back({-1,0});
    for (auto number: numbers){
        std::cout << number << std::endl;
    }
}

void test_strtoc(){
    std::vector<std::string> numbers({"+1i","-1i", "+1", "-1", "+1.2","-1.2","+4i","-3.2i","+1.2+4i","+1.2-83.3i"});
    for (auto num: numbers){
        std::cout<< num << " " << strtoc(num) <<std::endl;
    }
}