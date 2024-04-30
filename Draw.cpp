///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Define the Draw class
///
/// @file   Draw.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cassert>    // For assert
#include <climits>    // For UCHAR_MAX
#include <cstdint>    // For uint8_t
#include <cstring>    // For memset
#include <iomanip>    // For setw
#include <sstream>    // For ostringstream
#include <stdexcept>  // For invalid_argument

#include "Draw.h"  // For obvious reasons

#include "Game.h"

using namespace std;


/// Create a new Draw for a Game
///
/// @param newGame The Game associated with this drawing
Draw::Draw( const Game& newGame ) : game( newGame ) {
   /// Initialize all the draws to 0 (in groups of 8 draws)
   draw.g8[0] = 0;
   draw.g8[1] = 0;

   /// The fun of this function is how to efficiently and correctly generate
   /// a sorted set of numbers.  We will use a radix sort to select a set of
   /// balls out of a pool.

   alignas( 8 ) uint8_t pool[ MAX_BALLS ];  ///< Numbers to draw from
   memset( pool, 0, sizeof( pool ) );       //   0 means they number/ball is in the pool

   const uint8_t balls = newGame.getBalls();
//printf( "===\n" );
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      /// - Get a random index into the pool
      /// - If that index has been drawn (pool[r] != 0, iterate forward (and
      ///   wrap if necessary) until we find an unused number.
      uint8_t randIndex = getRandom8( balls );
//printf( "r %d  ", randIndex );

      while( pool[ randIndex ] != 0 ) {
//printf( "pool[%d]=%d  ", randIndex, pool[randIndex] );
         randIndex = ( (randIndex+1) >= balls ) ? 0 : (randIndex + 1);
//printf( "randIndex %d  ", randIndex );
      }
      assert( pool[ randIndex ] == 0 );
      pool[ randIndex ] = 1;
//printf( "DDD %d  balls=%d\n", randIndex, balls );
   }

   int found = 0;
   for( int ball = 0 ; ball < game.getBalls() ; ball++ ) {
      if( pool[ ball ] != 0 ) {
         draw.each[ found ] = ball;
         found++;
      }
   }
}


/// Copy constructor
///
/// @param rhs_draw The Draw object to copy **from**
Draw::Draw( const Draw& rhs_draw ) : game{ rhs_draw.game }, draw { rhs_draw.draw } {
}


/// Get a random number from 0 to the number of balls in the Lottery
///
/// @param balls The number of balls in the Game
///
/// @return An 8-bit random number
uint8_t Draw::getRandom8( uint8_t balls ) {
   uint8_t rval;

   asm volatile (
       "try_again:"
       "rdrand ax;"           /// If CF==0, then the rdrand failed... try again
       "jnc    try_again;"
       "AND    ax, 0x00FF;"   // Ensure the random number is <= 255
       "mov    cl, %[balls];"
       "div    cl;"
       "mov    %[rval], ah;"
      :[rval] "=r" ( rval )   // Output
      :[balls] "r" ( balls )  // Input
      :"ax", "cl", "cc"   );  // Clobbers

   return rval;
}


/// Validate that the compiler is compatible with the assumptions
/// Draw makes about data sizes.  This really only needs to be run once.
///
/// Like the other `validate` functions, it either returns `true` or raises
/// an exception (in this case, it fails an assert()).
///
/// @return `true` if Draw's data structure will compile and work correctly.
bool Draw::validate_static() {
   static_assert( MAX_BALLS <= UCHAR_MAX );

   return true;
}


/// Validate the internal state of the Draw
///
/// @return `true` if the state is valid.  If not, throw an exception.
bool Draw::validate() const {
   game.validate();

   const int draws = game.getDraws();
   const int balls = game.getBalls();

   int current = -1;
   for( int i = 0 ; i < draws ; i++ ) {
      if( current >= draw.each[ i ] ) {
         game.dump();
         dump();
         throw logic_error( "Draws are out of order" );
      }

      if( draw.each[ i ] >= balls ) {
         throw logic_error( "A ball is too large" );
      }
      current = draw.each[ i ];
   }

   return true;
}


/// Print the internal state of the Draw
///
///     Object              class               Draw
///     Object              this                0x7ffcfa8374b0
///     Draw                draw                  1   3   7   9  10  11  12  15
///
void Draw::dump() const {
   PRINT_CLASS_FOR_DUMP();
   /// We choose not to print the entire Game each time we print a Draw

   ostringstream stringBuffer;
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      stringBuffer << setfill( ' ' );
      stringBuffer << setw( 3 );
      stringBuffer << +draw.each[ i ] << " ";
   }

   FORMAT_LINE_FOR_DUMP( "Draw", "draw" ) << stringBuffer.str() << '\n';
}


/// Compare two Draw objects with `==`
///
/// @param rhs_draw The Draw on the right side of the `==`
///
/// @return `true` if the two Draw objects have the same values... `false` if not
bool Draw::operator == ( const Draw& rhs_draw ) const {
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      if( draw.each[i] != rhs_draw.draw.each[i] ) {
         return false;
      }
   }

   return true;
}


/// Compare two Draw objects with `!=`
///
/// @param rhs_draw The Draw on the right side of the `!=`
///
/// @return `true` if the two Draw objects are different... `false` if not
bool Draw::operator != ( const Draw& rhs_draw ) const {

   return ! operator==( rhs_draw ) ;
}


/// Compare two Draw objects with `<`
///
/// @param rhs_draw The Draw on the right side of the `<`
///
/// @return `true` if the left Draw object is less than the right... `false` if not
bool Draw::operator <  ( const Draw& rhs_draw ) const {
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      if( draw.each[i] < rhs_draw.draw.each[i] ) {
         return true;
      }
   }

   return false;
}

