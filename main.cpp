#include <string>
#include "src/test_file.cpp"

#include "src/complex.h"
#include "src/matrix.h"

const int TEST_COUNT = 6;

int main() {
    // // auto vector = std::vector<std::vector<C>>({{C(1,0), C(1,2), C(3,7)}, {C(2,3), C(3,4), C(0,-8)}, {C(9,-7), C(6,8), C(9,-19)}});
    // // auto m = Matrix<C>(vector);
    // auto vector = std::vector<std::vector<double>>({{2,5,4}, {-2,4,3}, {1,0,-2}});
    // // auto vector = std::vector<std::vector<double>>({{0,5,4}, {0,4,3}, {2,0,-2}});
    // auto m = Matrix<double>(vector);
    // m.printMatrix();
    // // m.swapRows(0,1);
    // // m.printMatrix();
    // std::cout<< m.determinantElementary()<<std::endl;
    //m.printMatrix();

    for (int i=0; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        testFile(prefix.append(test_number).append(postfix));
    }
    return 0;
}
