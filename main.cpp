#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include "src/matrix.h"

using namespace std;

const bool IS_DEBUG = false;

double strtod(const std::string& str){
    double temp = 0;
    auto it = str.begin();
    while (it!=str.end() && *it!='.')
        temp=temp*10+(int(*(it++))-'0');
    if (it++ == str.end())
        return temp;
    double graduation = 0.1;
    while (it!=str.end()){
        temp = temp + graduation * (int(*(it++))-'0');
        graduation*=0.1;
    }
    return temp;
}

// Parsing ifstream& to vector<vector<double>>
std::vector<std::vector<double>> parse(ifstream & file){
    string line;
    vector<vector<double>> data;
    while(getline(file, line)){
        vector<string> row_string;
        boost::algorithm::split(row_string, line, boost::is_any_of(" \t \n"));
        vector<double> row;
        for (auto& number: row_string){
            row.push_back(strtod(number));
        }
        data.push_back(row);
    }
    return data;
}

bool isFileValid(vector<vector<double>> data){
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++){
        if (data[i].size() != matrix_height){
            std::cout<<"Error on "<<i+1<<" row "<<std::endl;
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
            Matrix matrix(data);
            cout << "A:" << endl;
            matrix.printMatrix();
            auto det = matrix.determinant();
            cout<<"det A = "<< det << endl;
            if (det){
            cout<<"A^{-1}:"<< endl;
                Matrix reverseMatrix = matrix.inverseMatrix();
                reverseMatrix.printMatrix();
                std::cout<<"A*A^{-1}: "<<std::endl;
                (reverseMatrix*matrix).printMatrix();
            }
            else{
                cout<<"determinant = 0 => there is no inverse matrix"<< endl;
            }
        }
        else cout<<"Error (creating matrix)"<< endl;
    }
    else{
        cout<< "file isn't opened"<< endl;
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
