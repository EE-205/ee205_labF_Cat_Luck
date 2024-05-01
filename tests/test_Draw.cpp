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

#include "../Game.h"
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


   class TestDraw : public Draw {
   public:
      TestDraw( const Game& newGame ) : Draw( newGame ) {}

      void setDraw( int index, int value ) {
         draw.each[ index ] = value;
      }

      int getDraw( int index ) {
         return draw.each[ index ];
      }
   };


   BOOST_AUTO_TEST_CASE( test_lessThan_index_0 ) {
      Game aGame( MAX_BALLS, MAX_DRAWS, 1000 );
      TestDraw draw1( aGame );
      int index = MAX_DRAWS - 1;
      int value = MAX_BALLS - 1;
      // Initialize draw1 to 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249
      do {
         draw1.setDraw( index--, value-- );
      } while( index >= 0 );
      draw1.setDraw( 0, 0 );
//    draw1.dump();
      BOOST_CHECK( draw1.validate() );

      TestDraw draw2 = draw1;
//    draw2.dump();
      BOOST_CHECK( draw2.validate() );
      BOOST_CHECK( draw1 == draw2 );

      // Test draws at index 0
      for( int i = 1 ; i <= MAX_BALLS - MAX_DRAWS ; i++ ) {
         draw2.setDraw( 0, i );
//       draw2.dump();
         BOOST_CHECK( draw1 < draw2 );
      }
   }


   BOOST_AUTO_TEST_CASE( test_lessThan_index_15 ) {
      Game aGame( MAX_BALLS, MAX_DRAWS, 1000 );
      TestDraw draw1( aGame );
      // Initialize draw1 to 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249
      for( int i = 0 ; i < MAX_DRAWS ; i++ ) {
         draw1.setDraw( i, i );
      }
//    draw1.dump();
      BOOST_CHECK( draw1.validate() );

      TestDraw draw2 = draw1;
//    draw2.dump();
      BOOST_CHECK( draw2.validate() );
      BOOST_CHECK( draw1 == draw2 );


      // Test draws at index MAX_DRAWS
      for( int i = MAX_DRAWS ; i < MAX_BALLS ; i++ ) {
         draw2.setDraw( MAX_DRAWS-1, i );
         BOOST_CHECK( draw1 < draw2 );
      }
   }


   BOOST_AUTO_TEST_CASE( test_lessThan ) {
      Game aGame( MAX_BALLS, MAX_DRAWS, 1000 );
      for( int i = 0 ; i < 100000 ; i++ ) {
         TestDraw draw1( aGame );
         TestDraw draw2 = draw1;

         // Pick a random index (j) where the draw at that index won't wrap when incremented
         int j = rand() % MAX_DRAWS;
         while( true ) {
            // The draw can't be too big!
            if( draw2.getDraw( j ) >= MAX_BALLS - 1 ) {
               j = rand() % MAX_DRAWS;
               continue;
            }

            // The last draw is good
            if( j >= MAX_DRAWS-1 ) {
               break;
            }

            // If the next draw immediately follows the previous draw, then
            // find another index
            if( draw2.getDraw( j )+1 == draw2.getDraw( j + 1 ) ) {
               j = rand() % MAX_DRAWS;
               continue;
            }

            // All criteria is satisified... Use this j to increment draw2
            // making it just a little bigger than draw1
            break;
         }

         draw2.setDraw( j, draw2.getDraw( j ) + 1 );
         // draw2 has exactly 1 draw that's one more than draw1

//       draw1.dump();
         BOOST_CHECK( draw1.validate() );

//       draw2.dump();
         BOOST_CHECK( draw2.validate() );
         BOOST_CHECK( draw1 < draw2 );
      }
   }


BOOST_AUTO_TEST_SUITE_END()

/// @endcond
