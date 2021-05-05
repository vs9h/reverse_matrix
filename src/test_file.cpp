#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include "matrix.h"
#include "utils.h" // strtod, strtoc

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Parsing ifstream& to vector<vector<string>>
vector<vector<string>> parse(std::ifstream & file){
    vector<vector<string>> data;
    string line;

    while(getline(file, line)){
        vector<string> row;
        boost::algorithm::split(row, line, boost::is_any_of(" \t \n"));
        data.push_back(row);
    }
    return data;
}

bool isFileValid(vector<vector<string>> data){
    int matrix_height = data.size();
    for (int i=0; i<matrix_height; i++)
        if (data[i].size() != matrix_height){
            cout << "Error on " << i+1 << " row " << endl;
            return false;
        }
    return true;
}

enum class Matrix_Type { Real, Complex };

Matrix_Type define_matrix_type(vector<vector<string>> data){
    bool is_complex = false;
    for (const auto& row_string:data){
        if (is_complex) break;
        for (const auto& str: row_string){
            if (!is_complex && str.find('i') != string::npos)
                is_complex = true;
        }
    }
    return (is_complex) ? Matrix_Type::Complex : Matrix_Type::Real;
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

void processComplexMatrix(Matrix<C>& matrix){
    cout << "Matrix type = " << "Complex" << endl;
    cout << "A:" << endl;
    matrix.printMatrix();
    auto det = matrix.determinant();
    cout << "det A = " << det << endl;

    cout << "****************************" << endl;
    cout << "Check how operators works:" << endl;

    cout << "A * C(2,3):" << endl;
    auto mul = matrix * C(2.3); // you can also multiply int, double.
    mul.printMatrix();

    cout << "B:" << endl;
    auto sec = Matrix<C>(2,C(0,1));  
    sec.printMatrix();

    auto sum = matrix + sec;
    cout << "Sum (A+B):" << endl;
    sum.printMatrix();

    auto multiply = matrix * sec;
    cout << "Multiply (A*B):" << endl;
    multiply.printMatrix();

    cout << "Stop checking." << endl;
    cout << "****************************" << endl;
}

void processRealMatrix(Matrix<double>& matrix){
    cout << "Matrix type = " << "Real" << endl;
            
    matrix.printMatrix();
    auto det = matrix.determinant();
    cout << "Det A = "<< det << endl;
    if (det){
        cout << "A^{-1}:" << endl;
        auto reverseMatrix = matrix.inverseMatrix();
        reverseMatrix.printMatrix();
        cout << "A*A^{-1}: " << endl;
        (reverseMatrix*matrix).printMatrix();
    } else cout << "Determinant = 0 => there is no inverse matrix" << endl;
}

void testFile(string path){
    cout << "running file at path: " << path << endl;
    std::ifstream file(path);
    if (file.is_open())
    {
        // cout<< "file opened"<< endl;
        auto data = parse(file);
        
        if (!isFileValid(data)) { throw std::runtime_error("File isn't valid"); };
        auto matrix_type = define_matrix_type(data);

        if (static_cast<int>(matrix_type)==0){
            auto matrix = make_real_matrix(data);
            processRealMatrix(matrix);
        } else if (static_cast<int>(matrix_type)==1) {
            auto matrix = make_complex_matrix(data);
            processComplexMatrix(matrix);
        } else throw std::runtime_error("error with matrix_type");
    } else cout << "file isn't opened" << endl;
}