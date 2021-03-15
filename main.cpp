#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string.hpp>
#include "src/matrix.h"

const bool IS_DEBUG = false;

bool is_file_valid(std::ifstream & file){
    std::string line;
    std::vector<std::vector<double>> data;
    while(getline(file, line)){
        std::vector<std::string> row_string;
        boost::algorithm::split(row_string, line, boost::is_any_of(" \t \n"));
        std::vector<double> row;
        for (auto& number: row_string){
            row.push_back(std::stoi(number));
        }
        data.push_back(row);
    }
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++){
        if (data[i].size() != matrix_height){
            if (IS_DEBUG) std::cout<<"roflan pominki at "<<i+1<<" row "<<std::endl;
            return false;
        }
    }
    std::cout<<"matrix:"<<std::endl;
    Matrix rofl(data);
    rofl.printMatrix();
    std::cout<<"matrix/2"<<std::endl;
    Matrix rofl2 = rofl/2;
    rofl2.printMatrix();
    return true;
}

void check_file(std::string path){
    using std::cout;
    std::cout << "running file at path: "<< path<<std::endl;
    std::ifstream file(path);
    if (file.is_open())
    {
        if (IS_DEBUG) std::cout<< "file opened"<<std::endl;
        if (is_file_valid(file)){
            if (IS_DEBUG) cout<<"normalin"<<std::endl;
        };
    }
    else{
        if (IS_DEBUG) std::cout<< "file isn't opened"<<std::endl;
    }
}

const int TEST_COUNT = 4;

int main() {
    setlocale(LC_ALL, "ru");
    for (int i=1; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        check_file(prefix.append(test_number).append(postfix));
    }
    return 0;
}
