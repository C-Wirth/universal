#pragma once
// numeric_limits.hpp: definition of numeric_limits for fixed-size arbitrary configuration binary rational arithmetic types
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace std {

using namespace sw::universal;
/*
Trait class that identifies whether T is a literal type.

A literal type is a type that can qualify as constexpr. This is true for scalar types, references, certain classes, and arrays of any such types.

A class that is a literal type is a class (defined with class, struct or union) that :
1- has a trivial destructor,
2- every constructor call and any non - static data member that has brace - or equal - initializers is a constant expression,
3- is an aggregate type, or has at least one constexpr constructor or constructor template that is not a copy or move constructor, and
4- has all non - static data members and base classes of literal types

	TODO: how to make the decimal class a literal type so that we can use it as a return type for min/max/lowest etc.
*/
template <unsigned nbits, typename bt> 
class numeric_limits< sw::universal::rational<nbits,bt> >
{
	using RationalType = rational<nbits,bt>;
public:
	static constexpr bool is_specialized = true;
	static constexpr RationalType min() { return RationalType().minpos(); } // return minimum value
	static constexpr RationalType max() { return RationalType().maxpos();; } // return maximum value
	static constexpr RationalType lowest() { return RationalType().maxneg();; } // return most negative value
	static constexpr RationalType epsilon() { // return smallest effective increment from 1.0
		// the pattern is this ratio 0.....1 / 01.....0
		RationalType r(0, 0);
		r.setnbit(0);
		r.setdbit(nbits - 2);
		return r;
	}
	static constexpr RationalType round_error() { // return largest rounding error
		return long(0.5);
	}
	static constexpr RationalType denorm_min() {  // return minimum denormalized value
		return RationalType().minpos(); 
	}
	static constexpr RationalType infinity() { // return positive infinity
		return INT64_MAX; 
	}
	static constexpr RationalType quiet_NaN() { // return non-signaling NaN
		return RationalType(0, 0);
	}
	static constexpr RationalType signaling_NaN() { // return signaling NaN
		return RationalType(0, 0);
	}

	static constexpr int digits       = nbits;
	static constexpr int digits10     = 1000*nbits/3333;
	static constexpr int max_digits10 = digits10+1;
	static constexpr bool is_signed   = true;
	static constexpr bool is_integer  = true;
	static constexpr bool is_exact    = true;
	static constexpr int radix        = 10;

	static constexpr int min_exponent   = 0;
	static constexpr int min_exponent10 = 0;
	static constexpr int max_exponent   = 0;
	static constexpr int max_exponent10 = 0;
	static constexpr bool has_infinity  = false;
	static constexpr bool has_quiet_NaN = false;
	static constexpr bool has_signaling_NaN = false;
	static constexpr float_denorm_style has_denorm = denorm_absent;
	static constexpr bool has_denorm_loss = false;

	static constexpr bool is_iec559 = false;
	static constexpr bool is_bounded = false;
	static constexpr bool is_modulo = false;
	static constexpr bool traps = false;
	static constexpr bool tinyness_before = false;
	static constexpr float_round_style round_style = round_toward_zero;
};

}
