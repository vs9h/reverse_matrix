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
    mutable T cachedDetValue;
    mutable bool cacheValid{ false };
public:
    explicit Matrix(std::vector<std::vector<T>>& data)
            : size(data.size()) {
        this->data = std::vector<std::vector<T>>(data.size());
        for (int k=0; k<data.size(); k++)
            this->data[k] = std::vector<T>(data.size());
        for (int i=0; i<data.size(); ++i)
            for (int j=0; j<data.size(); ++j)
                (this->data)[i][j]=data[i][j];
    }

    explicit Matrix(std::size_t size, T value = 0)
        :size(size) {
        this->data = std::vector<std::vector<T>>(size);
        for (int k=0; k<size; k++)
            this->data[k] = std::vector<T>(size, value);
    }

    Matrix(const Matrix& rhs)
        :size(rhs.size) {
        this->data = std::vector<std::vector<T>>(size);
        for (int k=0; k<size; k++)
            this->data[k] = std::vector<T>(size);
        for (int i=0; i<size; ++i)
            for (int j=0; j<size; ++j)
                data[i][j] = rhs.data[i][j];
        if (rhs.cacheValid) {
            this->cachedDetValue = rhs.cachedDetValue;
            this->cacheValid = rhs.cacheValid;
        }
    }

    size_t getSize() const {
        return size;
    }

    Matrix operator*(const Matrix& rhs) {
        if (this->size!=rhs.size) throw std::runtime_error("You're trying to use operator * for matrix with different dimensions");
        auto res = Matrix(size);
        for (int i=0; i<size; ++i)
            for (int j=0; j<size; ++j)
                for (int k=0; k<size; ++k)
                    res[i][j]+=data[i][k]*rhs.data[k][j];
        if (this->cacheValid && rhs.cacheValid) {
            res.cachedDetValue = this->cachedDetValue * rhs.cachedDetValue;
            res.cacheValid = true;
        }
        return res;
    }

    Matrix operator+(const Matrix& rhs) {
        if (this->size!=rhs.size) throw std::runtime_error("You're trying to use operator + for matrix with different dimensions");
        auto res = Matrix(*this);
        if (res.cacheValid) res.setDetValid(false);
        for (int i=0; i<size; i++)
            for (int j=0; j<size; j++)
                res[i][j]+=rhs.data[i][j];
        return res;
    }

    Matrix operator-(const Matrix& rhs) {
        if (this->size!=rhs.size) throw std::runtime_error("You're trying to use operator - for matrix with different dimensions");
        auto res = Matrix(*this);
        if (res.cacheValid) res.setDetValid(false);
        for (int i=0; i<size; i++ )
            for (int j=0; j<size; j++)
                res[i][j]-=rhs.data[i][j];
        return res;
    }

    Matrix operator/(double number) {
        auto res = Matrix(*this);
        if (res.cacheValid) res.setDetValid(false);
        for (int i=0; i<size; ++i)
            for (int j=0; j<size; ++j)
                res[i][j]/=number;
        return res;
    }

    Matrix operator*(const T& number) { // Also works in this case: Matrix<C>*double, because in class C declared constructor C(double real).
        auto res = Matrix(*this);
        if (res.cacheValid) res.setDetValid(false);
        for (int i=0; i<size; ++i)
            for (int j=0; j<size; ++j)
                res[i][j]*=number;
        return res;
    }

    std::vector<T>& operator[](int row_index) {
        if (this->cacheValid) this->setDetValid(false);
        return data[row_index];
    }

    void printMatrix() const {
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++)
                std::cout << std::fixed << std::setprecision(2) << std::setw(5) << std::left << data[i][j] << ' ';
            std::cout<<std::endl;
        }
    }

    Matrix& transpose(){
        for (int i=0; i<size; ++i)
            for (int j=i; j<size; ++j)
                std::swap(data[i][j],data[j][i]);
        return *this;
    }

    Matrix makeMinor(Matrix& src, int r_excl, int c_excl) {
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

    Matrix inverseMatrix() {
        Matrix allied_matrix(this->size);
        for (int i=0; i<this->size; i++)
            for (int j=0; j<this->size; ++j)
                allied_matrix[i][j]=((i+j) % 2 ? -1: 1)* this->makeMinor(*this, i, j).determinant();
        allied_matrix.transpose();
        auto det = this->determinant();
        return allied_matrix/det;
    }
    
    void setDetValid(bool isValid) const {
        if (isValid){
            this->cacheValid = true;
        } else this-> cacheValid = false;
    }

    T determinant() {
        if (size == 1) return data[0][0];
        if (size == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        if (cacheValid){
            std::cout << "Take value drom cache" << std::endl;
            return this->cachedDetValue;
        } else {
            this->cachedDetValue = 0;
            for (int l = 0; l < size; l++)
                this->cachedDetValue += makeMinor(*this, 0, l).determinant() * data[0][l]*(l % 2 ? -1: 1);
            setDetValid(true);
            return this->cachedDetValue;
        }
    }
};