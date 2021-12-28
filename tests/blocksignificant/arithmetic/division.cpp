// division.cpp: functional tests for blocksignificant division
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
#include <universal/utility/long_double.hpp>
#include <iostream>
#include <iomanip>
#include <typeinfo>

#include <universal/native/integers.hpp>
#include <universal/internal/blocksignificant/blocksignificant.hpp>
#include <universal/verification/test_status.hpp> // ReportTestResult
#include <universal/verification/test_reporters.hpp> // ReportBinaryArithmeticError

// enumerate all multiplication cases for an blocksignificant<nbits,BlockType> configuration
template<size_t nbits, typename BlockType = uint8_t>
int VerifyDivision(bool reportTestCases) {
	int nrOfFailedTests = 0;
	/*
	constexpr size_t NR_VALUES = (size_t(1) << nbits);
	using namespace sw::universal;

	cout << endl;
	cout << "blocksignificant<" << nbits << ',' << typeid(BlockType).name() << '>' << endl;

	bool bReportOverflowCondition = false;

	int nrOfOverflows = 0;   // ref > maxpos
	int nrOfUnderflows = 0;  // ref < maxneg
	blocksignificant<nbits, BlockType> a, b, result, refResult;
	int64_t aref, bref, cref;
	for (size_t i = 0; i < NR_VALUES; i++) {
		a.set_raw_bits(i);
		aref = int64_t(a.to_long_long()); // cast to long long is reasonable constraint for exhaustive test
		for (size_t j = 0; j < NR_VALUES; j++) {
			b.set_raw_bits(j);
			bref = int64_t(b.to_long_long()); // cast to long long is reasonable constraint for exhaustive test
//			result = a / b;
		
			if (bref == 0) continue;
			cref = aref / bref;

			if (cref < -(1 << (nbits - 1))) {
				if (bReportOverflowCondition) cout << setw(5) << aref << " / " << setw(5) << bref << " = " << setw(5) << cref << " : ";
				if (bReportOverflowCondition) cout << "underflow: " << setw(5) << cref << " < " << setw(5) << -(1 << (nbits - 1)) << "(maxneg) assigned value = " << setw(5) << result.to_long_long() << " " << setw(5) << to_hex(result) << " vs " << to_binary(cref, 12) << endl;
				++nrOfUnderflows;
			}
			else if (cref > ((1 << (nbits - 1)) - 1)) {
				if (bReportOverflowCondition) cout << setw(5) << aref << " / " << setw(5) << bref << " = " << setw(5) << cref << " : ";
				if (bReportOverflowCondition) cout << "overflow: " << setw(5) << cref << " > " << setw(5) << (1 << (nbits - 1)) - 1 << "(maxpos) assigned value = " << setw(5) << result.to_long_long() << " " << setw(5) << to_hex(result) << " vs " << to_binary(cref, 12) << endl;
				++nrOfOverflows;
			}

			refResult.set_raw_bits(static_cast<uint64_t>(cref));
			if (result != refResult) {
				nrOfFailedTests++;
				if (reportTestCases)	ReportBinaryArithmeticError("FAIL", "/", a, b, result, cref);
			}
			else {
				// if (reportTestCases) ReportBinaryArithmeticSuccess("PASS", "/", a, b, result, cref);
			}
			if (nrOfFailedTests > 24) return nrOfFailedTests;
		}
		//		if (i % 1024 == 0) std::cout << '.';
	}
	cout << "Total State Space: " << setw(10) << NR_VALUES * NR_VALUES << " Overflows: " << setw(10) << nrOfOverflows << " Underflows " << setw(10) << nrOfUnderflows << endl;
	*/
	return nrOfFailedTests;
}

template<size_t nbits, typename BlockType>
void TestMostSignificantBit() {
	using namespace sw::universal;
	blocksignificant<nbits, BlockType> a;
	std::cout << to_binary(a) << ' ' << a.msb() << '\n';
	a.setbits(0x01ull);
	for (size_t i = 0; i < nbits; ++i) {
		std::cout << to_binary(a) << ' ' << a.msb() << '\n';
		a <<= 1;
	}
}

// conditional compile flags
#define MANUAL_TESTING 1
#define STRESS_TESTING 0

int main()
try {
	using namespace sw::universal;
	
	std::string test_suite  = "blocksignificant division validation";
	std::string test_tag    = "blocksignificant division";
	bool reportTestCases    = false;
	int nrOfFailedTestCases = 0;

	std::cout << test_suite << '\n';

#if MANUAL_TESTING

	TestMostSignificantBit<27, uint8_t>();
	TestMostSignificantBit<27, uint16_t>();
	TestMostSignificantBit<33, uint32_t>();

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<4, uint8_t>(reportTestCases), "blocksignificant<4>", "division");
//	nrOfFailedTestCases += ReportTestResult(VerifyDivision<8, uint8_t>(reportTestCases), "blocksignificant<8>", "division");

	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return EXIT_SUCCESS; // ignore failures
#else

#if REGRESSION_LEVEL_1
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<4, uint8_t>(reportTestCases), "blocksignificant<4,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<5, uint8_t>(reportTestCases), "blocksignificant<5,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<6, uint8_t>(reportTestCases), "blocksignificant<6,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<7, uint8_t>(reportTestCases), "blocksignificant<7,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<8, uint8_t>(reportTestCases), "blocksignificant<8,uint8_t>", "division");
#endif

#if REGRESSION_LEVEL_2
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<9, uint8_t>(reportTestCases), "blocksignificant<9,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<10, uint8_t>(reportTestCases), "blocksignificant<10,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<12, uint8_t>(reportTestCases), "blocksignificant<12,uint8_t>", "division");
#endif

#if REGRESSION_LEVEL_3
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<9, uint16_t>(reportTestCases), "blocksignificant<9,uint16_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<11, uint16_t>(reportTestCases), "blocksignificant<11,uint16_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<13, uint16_t>(reportTestCases), "blocksignificant<13,uint16_t>", "division");

	nrOfFailedTestCases += ReportTestResult(VerifyDivision<12, uint32_t>(reportTestCases), "blocksignificant<12,uint32_t>", "division");
#endif

#if REGRESSION_LEVEL_4
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<16, uint8_t>(reportTestCases), "blocksignificant<16,uint8_t>", "division");
	nrOfFailedTestCases += ReportTestResult(VerifyDivision<16, uint16_t>(reportTestCases), "blocksignificant<16,uint16_t>", "division");
#endif

	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
#endif  // MANUAL_TESTING
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
