#include <string>
#include "src/test_file.cpp"

#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include "src/matrix.h"
#include "src/utils.h" // strtod, strtoc

using std::cout;
using std::endl;
using std::string;
using std::vector;

Matrix<C> getMatrixByFile(string path){
    cout << "running file at path: " << path << endl;
    std::ifstream file(path);
    if (file.is_open())
    {
        auto data = parse(file);
        if (!isFileValid(data)) { throw std::runtime_error("File isn't valid"); };

        auto matrix = make_complex_matrix(data);
        return matrix;
    } else throw std::runtime_error("file isn't opened");
}

std::string fileNumberToPath(int i){
    std::string prefix = "../tests/";
    std::string test_number = std::to_string(i);
    std::string postfix = "-matrix_test.txt";
    return prefix.append(test_number).append(postfix);
}

int main() {
    
    auto A = getMatrixByFile(fileNumberToPath(0));
    auto B = getMatrixByFile(fileNumberToPath(1));   

    auto c = C(3,3);

    cout << "A:" << endl;
    A.printMatrix();

    cout << "B:" << endl;
    B.printMatrix();

    cout << "c:" << c << endl;

    cout << "A+B:" << endl;
    
    auto sum = A+B;
    sum.printMatrix();

    cout << "A-B:" << endl;
    auto sub = A+B;
    sub.printMatrix();

    cout << "A*c" << endl;
    auto mul = A*c;
    mul.printMatrix();

    cout << "A*B:" << endl;
    
    auto Mmul = A*B;
    Mmul.printMatrix();

    return 0;
}
