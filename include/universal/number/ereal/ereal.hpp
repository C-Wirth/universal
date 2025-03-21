// elastic multi-component floating-point arithmetic type standard header
//
// Copyright (C) 2017 Stillwater Supercomputing, Inc.
// SPDX-License-Identifier: MIT
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#ifndef _EREAL_STANDARD_HEADER_
#define _EREAL_STANDARD_HEADER_

////////////////////////////////////////////////////////////////////////////////////////
///  COMPILATION DIRECTIVES TO DIFFERENT COMPILERS
#include <universal/utility/compiler.hpp>
#include <universal/utility/architecture.hpp>
#include <universal/utility/bit_cast.hpp>
#include <universal/utility/long_double.hpp>

////////////////////////////////////////////////////////////////////////////////////////
/// required std libraries 
#include <iostream>
#include <iomanip>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////
///  BEHAVIORAL COMPILATION SWITCHES

////////////////////////////////////////////////////////////////////////////////////////
// enable throwing specific exceptions for integer arithmetic errors
// left to application to enable
#if !defined(EREAL_THROW_ARITHMETIC_EXCEPTION)
// default is to use std::cerr for signalling an error
#define EREAL_THROW_ARITHMETIC_EXCEPTION 0
#endif

///////////////////////////////////////////////////////////////////////////////////////
// bring in the trait functions
#include <universal/traits/number_traits.hpp>
#include <universal/traits/arithmetic_traits.hpp>
#include <universal/common/number_traits_reports.hpp>

////////////////////////////////////////////////////////////////////////////////////////
/// INCLUDE FILES that make up the library
#include <universal/number/ereal/exceptions.hpp>
#include <universal/number/ereal/ereal_fwd.hpp>
#include <universal/number/ereal/ereal_impl.hpp>
#include <universal/traits/ereal_traits.hpp>
//#include <universal/number/ereal/numeric_limits.hpp>

////////////////////////////////////////////////////////////////////////////////////////
// useful functions to work with ereals
#include <universal/number/ereal/attributes.hpp>
#include <universal/number/ereal/manipulators.hpp>

///////////////////////////////////////////////////////////////////////////////////////
/// math functions
//#include <universal/number/ereal/mathlib.hpp>

#endif
