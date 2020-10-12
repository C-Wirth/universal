#pragma once
// magric.hpp: generate a magic square matrix 
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <cstdint>
#include <random>
#include <algorithm>

namespace sw { namespace unum { namespace blas {

// fill a dense (N, N) matrix with linear index values in row order
template <typename Scalar>
matrix<Scalar> magic(size_t N) {
	using Matrix = matrix<Scalar>;
	typedef typename Matrix::size_type     size_type;

	if (N == 0) return matrix<Scalar>{};

	Matrix A(N, N);

	// generate a magic square matrix where all the rows, columns, and main diagonals sum to the same value
	// Three conditions:
	// 1- position of next number is calculated by rowIndex-1, colIndex+1, modulo N-1
	// 2- if number exists at new position, redo calculation as rowIndex+2, colIndex-2
	// 3- if row is 1 and column is N, new position is (0, n-2)
	//
	int i = static_cast<int>(N) / 2;
	int j = static_cast<int>(N) - 1;

	// generate the indices
	for (int e = 1; e <= static_cast<int>(N * N); /* increment in body */) {
		if (i == -1 && j == static_cast<int>(N)) {
			i = 0;
			j = static_cast<int>(N) - 2;
		}
		else {
			// first condition helper if next row index wraps around
			if (i < 0) i = static_cast<int>(N) - 1;;
			// first condition helper if next column index wraps around
			if (j == static_cast<int>(N)) j = 0;
		}
		if (A(static_cast<size_t>(i), static_cast<size_t>(j)) > Scalar(0)) { // second condition
			++i; j -= 2;
			continue;
		}
		else {
			A(static_cast<size_t>(i), static_cast<size_t>(j)) = Scalar(e++);
		}
		// first condition
		--i;
		++j;
	}

	return A;
}

}}} // namespace sw::unum::blas
