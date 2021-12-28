//  api.cpp : test suite runner for blocksignificant application programming interface tests
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
#include <universal/utility/long_double.hpp>
#include <iostream>

#include <universal/native/integers.hpp>
#include <universal/internal/blocksignificant/blocksignificant.hpp>

/*
A blocksignificant is a 2's complement binary encoding with a radix point that is aligned
with the hidden bit of the fraction encoding in a floating-point representation.

The main goal of the blocksignificant abstraction is to support arbitrary floating-point 
number systems with a high-quality, high-performance arithmetic engine.

The expensive part in these abstractions is the need to receive, expand, and align
bit strings, so special attention is given to fast implementations using copies.
This is acceptable, and leads to cleaner code, for small representations. However,
for very large representations these copies become prohibitive, and for those situations
the blocksignificant is not a good solution.

*/

template<typename blocksignificant>
void PrintRoundingDirection(const blocksignificant& a, size_t targetLsb) {
	std::cout << to_binary(a) << " target lsb = " << targetLsb << " ->rounding mode is " << (a.roundingDirection(targetLsb) ? "up" : "down") << '\n';
}

int main()
try {
	using namespace sw::universal;

	std::string tag = "blocksignificant storage class construction/conversion testing";

	{
		blocksignificant<7, uint8_t> a, b, c; // BitEncoding::Twos
		a.setbits(0x11); // 1.0 in 7-bit blocksignificant form
		b.setbits(0x11);
		std::cout << to_binary(a) << " : " << a << '\n';
		std::cout << to_binary(b) << " : " << b << '\n';
		c.add(a, b);
		std::cout << to_binary(c) << " : " << c << '\n';
		uint64_t fractionBits = c.fraction_ull();
		std::cout << to_binary(fractionBits, 4) << '\n';
	}

	{
		// a cfloat<8,2> has 5 fraction bits
		// a 00h.fffff format is thus 8 bits
		// By design, the 00h.fffff format contains all the valid values
		// for addition and subtraction.
		blocksignificant<8, uint8_t> a, b, c; // BitEncoding::Twos
		a.setbits(0x21); // 1.0 in 8-bit blocksignificant form
		b.setbits(0x21);
		std::cout << to_binary(a) << " : " << a << '\n';
		std::cout << to_binary(b) << " : " << b << '\n';
		c.add(a, b);
		std::cout << to_binary(c) << " : " << c << '\n';
		uint64_t fractionBits = c.fraction_ull();
		std::cout << to_binary(fractionBits, 5) << '\n';
	}

	{
		blocksignificant<12, uint8_t> a, b, c; // BitEncoding::Twos
		a.setbits(0x100);
		b.setbits(0x200);
		b.twosComplement();
		std::cout << to_binary(a) << " : " << a << '\n';
		std::cout << to_binary(b) << " : " << b << '\n';
		c.add(a, b);
		std::cout << to_binary(c) << " : " << c << '\n';
		uint64_t fractionBits = c.fraction_ull();
		std::cout << to_binary(fractionBits, 9) << '\n';
	}

	{
		// ad-hoc rounding test 
		// 0000'0000  lsb target is at(3)
		blocksignificant<8, uint8_t> a;  // BitEncoding::Ones
		size_t lsbTarget = 3;
		a.setbits(0x0F);	// 00001111  up
		PrintRoundingDirection(a, lsbTarget);
		a.setbits(0x07); 	// 00000111  up
		PrintRoundingDirection(a, lsbTarget);
		a.setbits(0x03);	// 00000011  down
		PrintRoundingDirection(a, lsbTarget);
		a.setbits(0x04); 	// 00000100  up: tie, round to even, which is down in this case
		PrintRoundingDirection(a, lsbTarget);
		a.setbits(0x0C); 	// 00001100  up: tie, round to even, which is up in this case
		PrintRoundingDirection(a, lsbTarget);
	}
}
catch (char const* msg) {
	std::cerr << msg << '\n';
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << '\n';
	return EXIT_FAILURE;
}
