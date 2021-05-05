#include <string>
#include "src/test_file.cpp"

#include "src/complex.h"
#include "src/matrix.h"

const int TEST_COUNT = 6;

std::string fileNumberToPath(int i){
    std::string prefix = "../tests/";
    std::string test_number = std::to_string(i);
    std::string postfix = "-matrix_test.txt";
    return prefix.append(test_number).append(postfix);
}

int main() {
   

    for (int i=0; i<=TEST_COUNT; ++i){
        testFile(fileNumberToPath(i));
    }
    return 0;
}
