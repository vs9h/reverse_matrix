#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include "src/matrix.h"
#include "src/complex.h"

using namespace std;

const bool IS_DEBUG = false;

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



// Parsing ifstream& to vector<vector<double>>
std::vector<std::vector<string>> parse(ifstream & file){
    string line;
    vector<vector<string>> data;
    //bool is_complex = false;

    // save initial data in vector<string> data_init and check matrix type (complex/double)
    //vector<string> data_init;
    while(getline(file, line)){
        // data_init.push_back(line);
        vector<string> row;
        boost::algorithm::split(row, line, boost::is_any_of(" \t \n"));
        data.push_back(row);
        // if (!is_complex && line.find('i') != std::string::npos)
        //     is_complex = true;
    }
    return data;
    //for (auto line: data_init){

        // vector<string> row_string;
        // boost::algorithm::split(row_string, line, boost::is_any_of(" \t \n"));
        // if (is_complex){
        //     vector<C> row;
        //     for (auto& number: row_string){
        //         std::cout << strtoc(number)<<std::endl;
        //         row.push_back(strtoc(number));
        //     }
        // }
        // vector<double> row;
        // for (auto& number: row_string){
        //     std::cout<<number<< ' ';
        //     // row.push_back(strtod(number));
        // }
        // std::cout<<std::endl;
        // data.push_back(row);
    //}
    // return data;
}

bool isFileValid(vector<vector<string>> data){
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++)
        if (data[i].size() != matrix_height){
            std::cout<<"Error on "<< i+1 <<" row "<<std::endl;
            return false;
        }
    return true;
}

enum class Matrix_Type { Real, Complex };

// string to C, input string example: "+1+8i", "-9i", "+1i", "-1i"; (!!plus before im part )
C strtoc(const std::string& str){
    auto it = str.begin();
    auto prev_it = it;
    if (str[str.size()-1] != 'i') return C(strtod(str)); // осталось либо есть только мнимая часть либо и вещ и мнимая.
    int sign_count = 0;
    for (size_t i = 0; i<str.size(); ++i)
        if (str[i]=='-' || str[i]=='+')
            sign_count++;
    if (sign_count == 1){// мнимая часть только
        return C(0,strtod(str.substr(0,str.size()-1)));
    }
    
    if (sign_count == 2){
        auto find_second_sign = std::find(str.begin()+1, str.end(), '+');
        if (find_second_sign == str.end())
            find_second_sign = std::find(str.begin()+1, str.end(), '-');
        size_t first_part_end = min(str.find('+', 1), str.find('-',1));
        // std::cout<< "fp="<<str.substr(0, first_part_end)<<endl;
        // std::cout<< "sc="<<str.substr(first_part_end, str.length()-first_part_end-1)<<endl;
        return C(strtod(str.substr(0, first_part_end)), strtod(str.substr(first_part_end, str.length()-first_part_end-1)));
        // std::cout<<"find -="<<*find_second_sign<<endl;
    }
    return C();
    // auto i_pos = str.find("i");
    // if (i_pos == std::string::npos){ // not found => only real part;
    //     return C(strtod(str));
    // }
    // std::cout<< "PROCESS: "<<str<<std::endl;
    // if (str.find("+i") != std::string::npos){
    //     if (str.find("+i")==0) return C(0,1);
    //     std::cout<< "substr:"<<str.find("+i");
    // } else if (str.find("-i") != std::string::npos){
    //     if (str.find("-i")==0) return C(0,-1);
    //     std::cout<< "substr:"<< str.substr(0, str.find("-i"));
    // }
}

auto make_complex_matrix(const vector<vector<string>> & data){
    vector<vector<C>> res;
    for (const auto& row_string: data){
        vector<C> row;
        for (const auto& number: row_string)
            row.push_back(strtoc(number));
        res.push_back(row);
    }
    return Matrix<C>(res);
}

auto make_real_matrix(const vector<vector<string>> & data){
    vector<vector<double>> res;
    for (const auto& row_string: data){
        vector<double> row;
        for (const auto& number: row_string)
            row.push_back(strtod(number));
        res.push_back(row);
    }
    return Matrix<double>(res);
}    

Matrix_Type define_matrix_type(vector<vector<string>> data){
    bool is_complex = false;
    for (const auto& row_string:data){
        if (is_complex) break;
        for (const auto& str: row_string){
            if (!is_complex && str.find('i') != std::string::npos)
                is_complex = true;
        }
    }
    return (is_complex) ? Matrix_Type::Complex : Matrix_Type::Real;
}

void testFile(std::string path){
    cout << "running file at path: "<< path << endl;
    ifstream file(path);
    if (file.is_open())
    {
        if (IS_DEBUG) std::cout<< "file opened"<< endl;
        auto data = parse(file);
        if (!isFileValid(data)) { throw runtime_error("File isn't valid"); };
        auto matrix_type = define_matrix_type(data);
        std::cout<< "type = ";
        if (static_cast<int>(matrix_type)==1){
            std::cout<<"Complex matrix"<<std::endl;
            auto matrix = make_complex_matrix(data);
            matrix.printMatrix();
            auto det = matrix.determinant();
            cout<<"det A = "<< det << endl;
        
            // auto mul = matrix*2.3;// тут можно и на C(a,b) умножать.
            // mul.printMatrix();
            // auto secm = Matrix<C>(2,C(0,1));  
            // cout<<"secm"<<endl;
            // secm.printMatrix();
            // cout<<"res"<<endl;
            // auto new_m = matrix+secm;
            // new_m.printMatrix();
            // auto multiply = matrix*secm;
            // cout<<"multiply"<<endl;
            // multiply.printMatrix();
        } else {
            std::cout<<"Real matrix"<<std::endl;
            auto matrix = make_real_matrix(data);
            matrix.printMatrix();
            auto det = matrix.determinant();
            cout<<"det A = "<< det << endl;
            if (det){
                cout<<"A^{-1}:"<< endl;
                auto reverseMatrix = matrix.inverseMatrix();
                reverseMatrix.printMatrix();
                std::cout<<"A*A^{-1}: "<<std::endl;
                (reverseMatrix*matrix).printMatrix();
            }
            else{
                cout<<"determinant = 0 => there is no inverse matrix"<< endl;
            }
        
        }
    }
    else{
        cout<< "file isn't opened"<< endl;
    }
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
    std::vector<string> numbers({"+1i","-1i", "+1", "-1", "+1.2","-1.2","+4i","-3.2i","+1.2+4i","+1.2-83.3i"});
    for (auto num: numbers){
        std::cout<< num << " "<< strtoc(num)<<"-ans "<<std::endl;
    }
}

const int TEST_COUNT = 5;

int main() {
    setlocale(LC_ALL, "ru");

    for (int i=4; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        testFile(prefix.append(test_number).append(postfix));
    }
    return 0;
}
