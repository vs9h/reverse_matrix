#include <vector>
#include <iostream>

class Matrix{
    size_t size;
    std::vector<std::vector<double>> data;

public:
    Matrix(std::vector<std::vector<double>>& data)
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

    size_t getSize(){
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
};