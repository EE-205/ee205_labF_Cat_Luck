///////////////////////////////////////////////////////////////////////////////
//   University of Hawaii, College of Engineering
//   Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//   Cats make their own luck
//
/// Comprehensive test of the Game class
///
/// @file test_Game.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
/// @cond Suppress Doxygen warnings

#define BOOST_TEST_MODULE Lucky_Cat_Test_Suite
#include <boost/test/included/unit_test.hpp>

#include "../Game.h"

using namespace std;

BOOST_AUTO_TEST_SUITE( test_Game )

   BOOST_AUTO_TEST_CASE( test_Constructor ) {
      BOOST_CHECK_THROW( Game( MIN_BALLS - 1, 10, 10 ), invalid_argument );
      BOOST_CHECK_NO_THROW( Game( MIN_BALLS, 10, 10 ) );
      BOOST_CHECK_NO_THROW( Game( MAX_BALLS, 10, 10 ) );
      BOOST_CHECK_THROW( Game( MAX_BALLS + 1, 10, 10 ), invalid_argument );
   }

BOOST_AUTO_TEST_SUITE_END()

/// @endcond
