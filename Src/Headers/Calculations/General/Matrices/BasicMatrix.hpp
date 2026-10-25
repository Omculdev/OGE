#pragma once
#include "Calculations/General/Types.hpp"
#include <type_traits>
#include <array>
#include <utility>
template <typename Type, usize rows, usize columns>
requires std::is_arithmetic_v<Type>
class BasicMatrix {
protected:
	std::array<std::array<Type, rows>, columns> matrix = {};
public:
	explicit BasicMatrix(const std::array<std::array<Type, rows>, columns>& mat) : matrix(mat) {}
	explicit BasicMatrix(std::array<std::array<Type, rows>, columns>&& mat) noexcept : matrix(std::move(mat)) {}
	explicit BasicMatrix(Type mat[rows][columns]) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				matrix[column][row] = mat[row][column];
			}
		}
	}
	BasicMatrix(const BasicMatrix<Type, rows, columns>& other) :
		matrix(other.matrix)
	{}
	BasicMatrix<Type, rows, columns>& operator=(const BasicMatrix<Type, rows, columns>& other) {
		if (&other == this) return *this;
		matrix = other.matrix;
		return *this;
	}
	BasicMatrix(BasicMatrix<Type, rows, columns>&& other) noexcept :
		matrix(std::move(other.matrix))
	{}
	BasicMatrix<Type, rows, columns>& operator=(BasicMatrix<Type, rows, columns>&& other) noexcept {
		if (&other == this) return *this;
		matrix = std::move(other.matrix);
		return *this;
	}
	Type& operator[](usize row, usize column) {
		return matrix[column][row];
	}
	const Type& operator[](usize row, usize column) const {
		return matrix[column][row];
	}
	Type& at(usize row, usize column) {
		return matrix.at(column).at(row);
	}
	const Type& at(usize row, usize column) const {
		return matrix.at(column).at(row);
	}
	auto operator<=>(const BasicMatrix<Type, rows, columns>& other) const = default;
	BasicMatrix<Type, columns, rows> getTransposed() const {
		BasicMatrix<Type, columns, rows> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[column, row] = (*this)[row, column];
			}
		}
		return newmatrix;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> operator+(ScalarType scalar) const {
		BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] + scalar;
			}
		}
		return newmatrix;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> operator-(ScalarType scalar) const {
		BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] - scalar;
			}
		}
		return newmatrix;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> operator*(ScalarType scalar) const {
		BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] * scalar;
			}
		}
		return newmatrix;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> operator/(ScalarType scalar) const {
		BasicMatrix<std::common_type_t<Type, ScalarType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] / scalar;
			}
		}
		return newmatrix;
	}
	template <typename MatrixType>
	requires std::is_arithmetic_v<MatrixType>
	BasicMatrix<std::common_type_t<Type, MatrixType>, rows, columns> operator+(const BasicMatrix<MatrixType, rows, columns>& other) const {
		BasicMatrix<std::common_type_t<Type, MatrixType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] + other.matrix[row, column];
			}
		}
		return newmatrix;
	}
	template <typename MatrixType>
	requires std::is_arithmetic_v<MatrixType>
	BasicMatrix<std::common_type_t<Type, MatrixType>, rows, columns> operator-(const BasicMatrix<MatrixType, rows, columns>& other) const {
		BasicMatrix<std::common_type_t<Type, MatrixType>, rows, columns> newmatrix = {};
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				newmatrix[row, column] = (*this)[row, column] - other.matrix[row, column];
			}
		}
		return newmatrix;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<Type, rows, columns>& operator+=(ScalarType scalar) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] += scalar;
			}
		}
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<Type, rows, columns>& operator-=(ScalarType scalar) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] -= scalar;
			}
		}
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<Type, rows, columns>& operator*=(ScalarType scalar) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] *= scalar;
			}
		}
		return *this;
	}
	template <typename ScalarType>
	requires std::is_arithmetic_v<ScalarType>
	BasicMatrix<Type, rows, columns>& operator/=(ScalarType scalar) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] /= scalar;
			}
		}
		return *this;
	}
	template <typename MatrixType>
	requires std::is_arithmetic_v<MatrixType>
	BasicMatrix<Type, rows, columns>& operator+=(const BasicMatrix<MatrixType, rows, columns>& other) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] += other[row, column];
			}
		}
		return *this;
	}
	template <typename MatrixType>
	requires std::is_arithmetic_v<MatrixType>
	BasicMatrix<Type, rows, columns>& operator-=(const BasicMatrix<MatrixType, rows, columns>& other) {
		for (usize row = 0; row < rows; row++) {
			for (usize column = 0; column < columns; column++) {
				(*this)[row, column] -= other[row, column];
			}
		}
		return *this;
	}
};