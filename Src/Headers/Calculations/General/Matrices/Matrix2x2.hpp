#pragma once
#include <array>
#include <type_traits>
#include "Calculations/General/Matrices/BasicMatrix.hpp"
template <typename Type>
requires std::is_arithmetic_v<Type>
class Matrix2x2 : public BasicMatrix<Type, 2, 2> {
public:
	explicit Matrix2x2(
		Type i1j1, Type i1j2,
		Type i2j1, Type i2j2
	) : BasicMatrix<Type, 2, 2>(std::array<std::array<Type, 2>, 2>{{i1j1, i2j1}, { i1j2, i2j2 }}) {}
	template <typename MatrixType>
	requires std::is_arithmetic_v<MatrixType>
	Matrix2x2<std::common_type_t<Type, MatrixType>> operator*(const Matrix2x2<MatrixType>& other) const {
		Matrix2x2<std::common_type_t<Type, MatrixType>> newmatrix = {};
		newmatrix[0, 0] = (*this)[0, 0] * other[0, 0] + (*this)[0, 1] * other[1, 0];
		newmatrix[1, 0] = (*this)[0, 0] * other[0, 1] + (*this)[0, 1] * other[1, 1];
		newmatrix[0, 1] = (*this)[1, 0] * other[0, 0] + (*this)[1, 1] * other[1, 0];
		newmatrix[1, 1] = (*this)[1, 0] * other[0, 1] + (*this)[1, 1] * other[1, 1];
		return newmatrix;
	}
	Type getDeterminant() const {
		return (*this)[0, 0] * (*this)[1, 1] - (*this)[0, 1] * (*this)[1, 0];
	}
};
using FloatMatrix2x2 = Matrix2x2<f32>;
using IntMatrix2x2 = Matrix2x2<i32>;
using UIntMatrix2x2 = Matrix2x2<u32>;