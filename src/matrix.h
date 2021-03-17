#include <vector>
#include <iostream>

class Matrix{
public: // надо будет потом пофиксить, добавив оператор [].
    size_t size;
    std::vector<std::vector<double>> data;

public:
    explicit Matrix(std::vector<std::vector<double>>& data)
            : size(data.size()) {
        this->data = std::vector<std::vector<double>>(data.size());
        for (int k=0; k<data.size(); k++)
            this->data[k] = std::vector<double>(data.size());
        for (int i=0; i<data.size(); ++i){
            for (int j=0; j<data.size(); ++j){
                (this->data)[i][j]=data[i][j];
            }
        }
    };

    explicit Matrix(std::size_t size, double value = 0)
        :size(size) {
        this->data = std::vector<std::vector<double>>(size);
        for (int k=0; k<size; k++)
            this->data[k] = std::vector<double>(size, value);
        //std::cout<<"print matrix"<<std::endl;
        //this->printMatrix();
    }

    size_t getSize() const {
        return size;
    }

    Matrix& operator+(const Matrix& rhs ){
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++){
                data[i][j]+=rhs.data[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*(const Matrix& rhs ){
        std::vector<std::vector<double>> res_data(rhs.size);
        for (int k=0; k<data.size(); k++)
            res_data[k] = std::vector<double>(data.size());
        for (int i=0; i<size; ++i ){
            for (int j=0; j<size; ++j){
                res_data[i][j]=0;
                for (int k=0; k<size; ++k){
                    res_data[i][j]+=data[i][k]*rhs.data[k][j];
                }
            }
        }
        for (int i=0; i<size; ++i){
            for (int j=0; j<size; ++j){
                data[i][j]=res_data[i][j];
            }
        }
        return *this;
    }
    Matrix& operator/(const double number){
        for (int i=0; i<size; ++i){
            for (int j=0; j<size; ++j){
                data[i][j]=data[i][j]/number;
            }
        }
        return *this;
    }

    void printMatrix(){
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++){
                std::cout<<data[i][j]<<' ';
            }
            std::cout<<std::endl;
        }
    }

    Matrix make_minor(const Matrix& src, int r_excl, int c_excl) {
        Matrix minor(src.getSize()-1);
        for (int i = 0, iminor = 0; i < src.getSize(); ++i) {
            if (i == r_excl)
                continue;
            for (int j = 0, jminor = 0; j < src.getSize(); ++j) {
                if (j == c_excl)
                    continue;
                minor.data[iminor][jminor] = src.data[i][j];
                ++jminor;
            }
            ++iminor;
        }
        return minor;
    }

    // solution from https://www.cyberforum.ru/cpp-beginners/thread2337509.html
    double determinant() {

        if (size == 1) return data[0][0];
        if (size == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        double det = 0;
        for (int l = 0; l < size; l++) {
            det += (l % 2 ? -1: 1) * data[0][l]*make_minor(*this, 0, l).determinant() ; // вычисляем определитель
        }
        return det;
    }

};