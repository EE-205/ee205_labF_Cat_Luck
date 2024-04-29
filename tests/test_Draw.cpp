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
         int max_test = i * 3;
         for( int j = 0 ; j < max_test ; j++ ) {
//          printf( "%3u ", Draw::getRandom8( i ) );
            BOOST_CHECK_LT( Draw::getRandom8( i ), i );
         }
//       puts( "" );
      }
   }

   BOOST_AUTO_TEST_CASE( test_Draw ) {
      for( int i = 1 ; i <= MAX_BALLS ; i++ ) {
         for( int j = 1 ; j <= MAX_DRAWS ; j++ ) {
            if( j > i ) {
               continue;
            }
            Game aGame( i, j, 1000 );
            for( int k = 0 ; k < 100 ; k++ ) {
               Draw aDraw( aGame );
               BOOST_CHECK( aDraw.validate() );
//             aDraw.dump();
            }
         }
      }


      // Iterate over all allowed draws to ensure that when balls==draws
      // continues to work (this stresses the picker algorithm).
      for( int i = 1 ; i < MAX_DRAWS ; i++ ) {
         for( int j = 0 ; j < i * 10 ; j++ ) {
            Game aGame( i, i, 1000 );
            Draw aDraw( aGame );
            BOOST_CHECK( aDraw.validate() );
//          aDraw.dump();

            // Let's check Games where there's one more ball than draws
            Game game1( i+1, i, 1000 );
            Draw draw2( game1 );
            BOOST_CHECK( draw2.validate() );
//          draw2.dump();
         }
      }
   }
   
   
   #define DRAWS_TO_CHECK (512)
   
   BOOST_AUTO_TEST_CASE( test_Equality ) {
      Game aGame( MAX_BALLS, MAX_DRAWS, 1000 );
      Draw* draws[ DRAWS_TO_CHECK ];
      for( int i = 0 ; i < DRAWS_TO_CHECK ; i++ ) {
         draws[i] = new Draw( aGame );
      }
      
      for( int i = 0 ; i < DRAWS_TO_CHECK ; i++ ) {
         for( int j = 0 ; j < DRAWS_TO_CHECK ; j++ ) {
            if( i == j ) {
               BOOST_CHECK( draws[i] == draws[j] );
            } else {
               BOOST_CHECK( draws[i] != draws[j] );
            }
         }
      }
   }

BOOST_AUTO_TEST_SUITE_END()

/// @endcond
