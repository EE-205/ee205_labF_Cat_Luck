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
#include <cstring>    // For memset

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

   uint8_t balls = newGame.getBalls();
//printf( "===\n" );
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      /// - Get a random index into the pool
      /// - If that index has been drawn (pool[r] != 0, iterate forward (and
      ///   wrap if necessary) until we find an unused number.
      uint8_t r = getRandom8( balls );
//printf( "r %d  ", r );

      while( pool[ r ] != 0 ) {
//printf( "pool[%d]=%d  ", r, pool[r] );
         r = ( (r+1) >= balls ) ? 0 : (r + 1);
//printf( "rrr %d  ", r );
      }
      assert( pool[r] == 0 );
      pool[ r ] = 1;
//printf( "DDD %d  balls=%d\n", r, balls );
   }

   int found = 0;
   for( int ball = 0 ; ball < game.getBalls() ; ball++ ) {
      if( pool[ ball ] != 0 ) {
         draw.each[ found ] = ball;
         found++;
      }
   }
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
   
   int draws = game.getDraws();
   int balls = game.getBalls();
   
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

   ostringstream sb;
   for( int i = 0 ; i < game.getDraws() ; i++ ) {
      sb << setfill( ' ' );
      sb << setw( 3 );
      sb << +draw.each[ i ] << " ";
   }

   FORMAT_LINE_FOR_DUMP( "Draw", "draw" ) << sb.str() << endl;
}
