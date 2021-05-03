#include "matrix.h"

// template<class T>
// Matrix<T> Matrix<T>::makeMinor(Matrix<T>& src, int r_excl, int c_excl) {
//     Matrix minor(src.getSize()-1);
//     for (int i = 0, iminor = 0; i < src.getSize(); ++i) {
//         if (i == r_excl)
//             continue;
//         for (int j = 0, jminor = 0; j < src.getSize(); ++j) {
//             if (j == c_excl)
//                 continue;
//             minor[iminor][jminor] = src[i][j];
//             ++jminor;
//         }
//         ++iminor;
//     }
//     return minor;
// }

// template<typename T>
// T Matrix<T>::determinant() {
//         if (size == 1) return data[0][0];
//         if (size == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

//         T det = 0;
//         for (int l = 0; l < size; l++) {
//             det += (l % 2 ? -1: 1) * data[0][l] * makeMinor(*this, 0, l).determinant() ; // вычисляем определитель
//         }
//         return det;
// }

// template<class T>
// Matrix<T> Matrix<T>::transpose() {
//     for (int i=0; i<size; ++i)
//         for (int j=i; j<size; ++j)
//             std::swap(data[i][j],data[j][i]);
//     return *this;
// }

// template<typename T>
// Matrix<T> Matrix<T>::inverseMatrix(){
    // Matrix<T> allied_matrix(this->size);
    // for (int i=0; i<this->size; i++){
    //     for (int j=0; j<this->size; ++j)
    //         allied_matrix[i][j]=((i+j) % 2 ? -1: 1)* this->makeMinor(*this, i, j).determinant();
    // }
    // allied_matrix.transpose();
    // auto det = this->determinant();
    // return allied_matrix/det;
// }