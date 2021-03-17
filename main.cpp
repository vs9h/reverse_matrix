#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string.hpp>
#include "src/matrix.h"

using namespace std;

const bool IS_DEBUG = false;

// Parsing ifstream& to vector<vector<double>>
std::vector<std::vector<double>> parse(ifstream & file){
    string line;
    vector<vector<double>> data;
    while(getline(file, line)){
        vector<string> row_string;
        boost::algorithm::split(row_string, line, boost::is_any_of(" \t \n"));
        vector<double> row;
        for (auto& number: row_string){
            row.push_back(stod(number));
        }
        data.push_back(row);
    }
    return data;
}

bool isFileValid(vector<vector<double>> data){
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++){
        if (data[i].size() != matrix_height){
            if (IS_DEBUG) std::cout<<"Error on "<<i+1<<" row "<<std::endl;
            return false;
        }
    }
    return true;
}

void testFile(std::string path){
    cout << "running file at path: "<< path << endl;
    ifstream file(path);
    if (file.is_open())
    {
        if (IS_DEBUG) std::cout<< "file opened"<< endl;
        auto data = parse(file);
        if (isFileValid(data)) {
            if (IS_DEBUG) std::cout << "normalin" << endl;
            Matrix matrix(data);
            cout << "matrix:" << endl;
            matrix.printMatrix();
            auto det = matrix.determinant();
            cout<<"det = "<< det << endl;
            if (det){
            cout<<"allied matrix:"<< endl;
            matrix.allied().printMatrix();
            }
            else{
                cout<<"determinant = 0 => not exists allied matrix = 0"<< endl;
            }
        }
        else cout<<"Error (creating matrix)"<< endl;
    }
    else{
        if (IS_DEBUG) cout<< "file isn't opened"<< endl;
    }
}

const int TEST_COUNT = 4;

int main() {
    setlocale(LC_ALL, "ru");
    for (int i=0; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        testFile(prefix.append(test_number).append(postfix));
    }
    return 0;
}
