///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Comprehensive test of the Draw class
///
/// @file test_Draw.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
/// @cond Suppress Doxygen warnings

#include <boost/test/unit_test.hpp>

#include "../Draw.h"

using namespace std;

#include <stdio.h>

BOOST_AUTO_TEST_SUITE( test_Draw )

   BOOST_AUTO_TEST_CASE( test_validateDraw ) {
      BOOST_CHECK( Draw::validate_static() );
   }

   BOOST_AUTO_TEST_CASE( test_getRandom8 ) {
      for( int i = 1 ; i < 10 ; i++ ) {
//       printf( "i=%d  ", i );
         int max_test = i * 10;
         for( int j = 0 ; j < max_test ; j++ ) {
//          printf( "%3u ", Draw::getRandom8( i ) );
            BOOST_CHECK_LT( Draw::getRandom8( i ), i );
         }
//       puts( "" );
      }
   }


BOOST_AUTO_TEST_SUITE_END()

/// @endcond
