#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

template<class T>
class Matrix{
private:
    size_t size;
    std::vector<std::vector<T>> data;
public:
    explicit Matrix(std::vector<std::vector<T>>& data)
            : size(data.size()) {
        this->data = std::vector<std::vector<T>>(data.size());
        for (int k=0; k<data.size(); k++)
            this->data[k] = std::vector<T>(data.size());
        for (int i=0; i<data.size(); ++i){
            for (int j=0; j<data.size(); ++j){
                (this->data)[i][j]=data[i][j];
            }
        }
    };

    explicit Matrix(std::size_t size, T value = 0)
        :size(size) {
        this->data = std::vector<std::vector<T>>(size);
        for (int k=0; k<size; k++)
            this->data[k] = std::vector<T>(size, value);
    }

    size_t getSize() const {
        return size;
    }

    Matrix<T>& operator*(const Matrix<T>& rhs ){
        std::vector<std::vector<T>> res_data(rhs.size);
        for (int k=0; k<data.size(); k++)
            res_data[k] = std::vector<T>(data.size());
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
    Matrix<T>& operator/(const double number){
        for (int i=0; i<size; ++i){
            for (int j=0; j<size; ++j){
                data[i][j]=data[i][j]/number;
            }
        }
        return *this;
    }

    Matrix<T>& operator*(const T& c){
        for (int i=0; i<size; ++i){
            for (int j=0; j<size; ++j){
                data[i][j]=data[i][j]*c;
            }
        }
        return *this;
    }

    Matrix<T>& operator+(const Matrix<T>& rhs ){
        if (this->size!=rhs.size) throw std::runtime_error("incorrect operation");
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++){
                data[i][j]+=rhs.data[i][j];
            }
        }
        return *this;
    }

    std::vector<T>& operator[](int row_index){
        return data[row_index];
    }

    void printMatrix(){
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++)
                std::cout <<  std::fixed << std::setprecision(2) <<std::setw(5)<<std::left <<data[i][j]<<' ';
            std::cout<<std::endl;
        }
    }

    Matrix<T> transpose(){
        for (int i=0; i<size; ++i)
            for (int j=i; j<size; ++j)
                std::swap(data[i][j],data[j][i]);
        return *this;
    }
    Matrix<T> makeMinor(Matrix& src, int r_excl, int c_excl){
        Matrix minor(src.getSize()-1);
        for (int i = 0, iminor = 0; i < src.getSize(); ++i) {
            if (i == r_excl)
                continue;
            for (int j = 0, jminor = 0; j < src.getSize(); ++j) {
                if (j == c_excl)
                    continue;
                minor[iminor][jminor] = src[i][j];
                ++jminor;
            }
            ++iminor;
    }
    return minor;
    }
    Matrix<T> inverseMatrix(){
        Matrix<T> allied_matrix(this->size);
        for (int i=0; i<this->size; i++){
            for (int j=0; j<this->size; ++j)
                allied_matrix[i][j]=((i+j) % 2 ? -1: 1)* this->makeMinor(*this, i, j).determinant();
        }
        allied_matrix.transpose();
        auto det = this->determinant();
        return allied_matrix/det;
    }
    T determinant() {
        if (size == 1) return data[0][0];
        if (size == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        T det = 0;
        for (int l = 0; l < size; l++) {
            det += makeMinor(*this, 0, l).determinant() * data[0][l]*(l % 2 ? -1: 1);
        }
        return det;
    }
};