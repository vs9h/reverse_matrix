#include <string>
#include "src/test_file.cpp"

const int TEST_COUNT = 4;

int main() {
    for (int i=0; i<=TEST_COUNT; ++i){
        std::string prefix = "../tests/";
        std::string test_number = std::to_string(i);
        std::string postfix = "-matrix_test.txt";
        testFile(prefix.append(test_number).append(postfix));
    }
    return 0;
}
