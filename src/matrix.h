#include <vector>
#include <iostream>

class Matrix{
private:
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
    }

    size_t getSize() const {
        return size;
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

    std::vector<double>& operator[](int row_index){
        return data[row_index];
    }

    void printMatrix(){
        for (int i=0; i<size; i++ ){
            for (int j=0; j<size; j++){
                std::cout<<data[i][j]<<' ';
            }
            std::cout<<std::endl;
        }
    }

    Matrix transpose();
    Matrix makeMinor(Matrix& src, int r_excl, int c_excl);
    Matrix allied();
    double determinant();
};