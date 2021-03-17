#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string.hpp>
#include "src/matrix.h"

const bool IS_DEBUG = true;

// Parsing ifstream& to vector<vector<double>>
std::vector<std::vector<double>> parse(std::ifstream & file){
    std::string line;
    std::vector<std::vector<double>> data;
    while(getline(file, line)){
        std::vector<std::string> row_string;
        boost::algorithm::split(row_string, line, boost::is_any_of(" \t \n"));
        std::vector<double> row;
        for (auto& number: row_string){
            row.push_back(std::stod(number));
        }
        data.push_back(row);
    }
    return data;
}

bool is_file_valid(std::vector<std::vector<double>> data){
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++){
        if (data[i].size() != matrix_height){
            if (IS_DEBUG) std::cout<<"Error on "<<i+1<<" row "<<std::endl;
            return false;
        }
    }
    return true;
}

void check_file(std::string path){
    std::cout << "running file at path: "<< path<<std::endl;
    std::ifstream file(path);
    if (file.is_open())
    {
        if (IS_DEBUG) std::cout<< "file opened"<<std::endl;
        auto data = parse(file);
        if (is_file_valid(data)) {
            if (IS_DEBUG) std::cout << "normalin" << std::endl;
            Matrix matrix(data);
            std::cout << "matrix:" << std::endl;
            matrix.printMatrix();
            std::cout<<"det = "<<matrix.determinant()<<std::endl;
        }
        else std::cout<<"Error (creating matrix)"<<std::endl;
    }
    else{
        if (IS_DEBUG) std::cout<< "file isn't opened"<<std::endl;
    }
}

const int TEST_COUNT = 4;

int main() {
    setlocale(LC_ALL, "ru");
    for (int i=0; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        check_file(prefix.append(test_number).append(postfix));
    }
    return 0;
}
